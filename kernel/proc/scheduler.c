/*
    scheduler.c - contains scheduler
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdint.h>
#include <string.h>
#include <kernel/kernel.h>
#include <kernel/system.h>
#include <kernel/tasking.h>

#define STACK_SIZE 8192

extern void pit_tick(regs* r);

thread* thread_idle = 0;

uint32_t alloc_kernel_stack()
{
    void* stack = (void*)kmalloc(STACK_SIZE);
    return (uint32_t)stack + STACK_SIZE;
}

thread* create_thread_int(void* thread_func, int owning_pid, int is_kernel, int creator, int is_init, void* user_stack, int is_idle)
{
    thread* new = 0;
    if(is_init == 0 && is_idle == 0)
        new = alloc_thread();
    else if(is_init == 1 && is_idle == 1)
    {
        new = kmalloc(sizeof(thread));
    }
    else
        new = alloc_init_thread();
    new->tid = alloc_tid();
    new->owning_pid = owning_pid;
    new->time_reminaing = TASK_QUANTAM;
    new->state = THREAD_STATE_SPAWNING;
    new->is_kernel = is_kernel;
    new->return_value = 0;
    if(creator != 0)
        new->parent = find_thread(creator);
    uint32_t kernel_stack = alloc_kernel_stack();
    int stack_size = STACK_SIZE;
    if(is_kernel == 1)
    {
        new->stack = kernel_stack;
        new->stack_size = stack_size;
    }
    else
    {
        new->stack = user_stack;
        new->stack_size = stack_size;
    }
    new->kernel_stack = kernel_stack;
    new->kernel_stack_size = stack_size;
    new->first_run = 1;
    new->sleep_delta = -1;
    if(!is_init)
        strcpy(new->working_dir, new->parent->working_dir);
    else
        strcpy(new->working_dir, "/");
    memset((void*)&new->regs, 0, sizeof(trap_frame));
    new->regs.eip = (uint32_t)thread_func;
    new->regs.esp = (uint32_t)new->stack;
    new->regs.ebp = (uint32_t)new->stack;
    process* parent = find_proc(owning_pid);
    new->dir = parent->p_dir;
    parent->threads[++parent->num_used_threads] = new->tid;
    new->regs.cr3 = parent->pdbr;
    uint16_t cs = 0;
    uint16_t ds = 0;
    if(is_kernel)
    {
        cs = 0x08;
        ds = 0x10;
    }
    else
    {
        cs = 0x1b;
        ds = 0x23;
    }
    new->regs.eflags = 0x202;
    new->regs.cs = cs;
    new->regs.ds = ds;
    new->regs.es = ds;
    new->regs.fs = ds;
    new->regs.gs = ds;
    new->regs.ss = ds;
    return new;
}

thread* create_thread(void* thread_func, int owning_pid, int is_kernel, int creator, int is_init, void* user_stack)
{
    create_thread_int(thread_func, owning_pid, is_kernel, creator, is_init, user_stack, 0);
}

int destroy_thread(int tid, int is_destroyed)
{
    disable();
    thread* to_destroy = find_thread(tid);
    int ret = to_destroy->return_value;
    to_destroy->state = THREAD_STATE_STOPPING;
    to_destroy->parent->return_value = ret;
    kfree(to_destroy->kernel_stack);
    uint32_t block = (uint32_t)get_physical_address(find_proc(to_destroy->owning_pid)->p_dir, to_destroy->stack);
    if((block & 0xFFFFF000))
    {
        block &= 0xFFFFF000;
        block += 0x1000;
    }
    block -= 4096;
    free_block((void*)block);
    enable();
    if(is_destroyed)
        for(;;);
    return ret;
}

process* create_process(pdirectory* p_dir, int parent_pid, uint32_t base, uint32_t size)
{
    process* new = alloc_process();
    new->pid = alloc_pid();
    memset(&new->threads, 0, sizeof(int) * 36);
    new->num_used_threads = -1;
    new->image_base = base;
    new->return_value = 0;
    new->image_size = size;
    new->p_dir = p_dir;
    new->pdbr = (uint32_t)&p_dir->entries;
    if(parent_pid)
        new->parent = find_proc(parent_pid);
    return new;
}

void scheduler_dispatch(regs* r)
{
    pit_tick(r);
    thread* running = get_queue_front();
    thread* iterator = running;
    if(running == 0)
        running = thread_idle;
    while(iterator->next != 0)
    {
        if(iterator->state == THREAD_STATE_STOPPING)
        {
            if(running->tid != iterator->tid)
            {
                thread* temp = iterator;
                iterator = iterator->next;
                delete_thread(temp);
                continue;
            }
            else
            {
                delete_front();
                running = get_queue_front();
            }
        }
        iterator = iterator->next;
    }
    if(running->time_reminaing != 0)
    {
        running->time_reminaing--;
        if(running->first_run == 1)
        {
            running->state = THREAD_STATE_RUNNING;
            running->first_run = 0;
        }
        else
        {
            running->regs.eax = r->eax;
            running->regs.ebx = r->ebx;
            running->regs.ecx = r->ecx;
            running->regs.edx = r->edx;
            running->regs.esi = r->esi;
            running->regs.edi = r->edi;
            running->regs.esp = r->useresp;
            running->regs.ebp = r->ebp;
            running->regs.eip = r->eip;
            running->regs.ds = r->ds;
            running->regs.cs = r->cs;
            running->regs.es = r->es;
            running->regs.fs = r->fs;
            running->regs.gs = r->gs;
            running->regs.ss = r->ds;
            running->regs.eflags = r->eflags;
        }
    }
    else if(running->time_reminaing == 0)
    {
        thread* new_pos = switch_thread();
        new_pos->state = THREAD_STATE_ACTIVE;
        new_pos->time_reminaing = TASK_QUANTAM;
        new_pos->regs.eax = r->eax;
        new_pos->regs.ebx = r->ebx;
        new_pos->regs.ecx = r->ecx;
        new_pos->regs.edx = r->edx;
        new_pos->regs.esi = r->esi;
        new_pos->regs.edi = r->edi;
        new_pos->regs.esp = r->useresp;
        new_pos->regs.ebp = r->ebp;
        new_pos->regs.eip = r->eip;
        new_pos->regs.ds = r->ds;
        new_pos->regs.cs = r->cs;
        new_pos->regs.es = r->es;
        new_pos->regs.fs = r->fs;
        new_pos->regs.gs = r->gs;
        new_pos->regs.ss = r->ss;
        new_pos->regs.eflags = r->eflags;
        new_pos->first_run = 1;
    }
    tss_set_stack(0x10, running->kernel_stack);
    r->eax = running->regs.eax;
    r->ebx = running->regs.ebx;
    r->ecx = running->regs.ecx;
    r->edx = running->regs.edx;
    r->esi = running->regs.esi;
    r->edi = running->regs.edi;
    r->cs = running->regs.cs;
    r->ds = running->regs.ds;
    r->es = running->regs.es;
    r->fs = running->regs.fs;
    r->gs = running->regs.gs;
    r->ss = running->regs.ss;
    r->useresp = running->regs.esp;
    r->ebp = running->regs.ebp;
    r->eip = running->regs.eip;
    r->eflags = running->regs.eflags;
    switch_dir(running->dir);
}

void idle_thread()
{
    for(;;) asm("pause");
}

void scheduler_init()
{
    serial_printf("[scheduler] Scheduler intializing.\r\n");
    disable();
    init_queue();
    create_process(get_kernel_directory(), 0, 0xC0000000, 0x20000000);
    thread* idle = create_thread_int(idle_thread, 1, 1, 0, 1, 0, 1);
    thread_idle = idle;
    irq_install_handler(0, scheduler_dispatch);
    serial_printf("[scheduler] Scheduler initialized.\r\n");
}
