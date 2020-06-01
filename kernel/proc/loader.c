/*
    loader.c - contains ELF loader
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <kernel/kernel.h>
#include <kernel/system.h>
#include <kernel/tasking.h>
#include <kernel/elf.h>

int aentry;
int stack;

extern uint32_t read_eip();
extern uint32_t read_esp();

#define PROC_BASE 0x08048000

extern void loader_internal();

void create_proc()
{
    int size = 0;
    void* buffer = read_file("hello/hello.elf", &size);
    elf32_hdr* p_hdr = (elf32_hdr*)buffer;
    if(p_hdr->e_ident[EI_MAG0] == ELFMAG0)
    {
        aentry = p_hdr->e_entry;
        int base = PROC_BASE;
        if(!(size & 0xFFFFF000))
        {
            size &= 0xFFFFF000;
            size += 0x1000;
        }
        pdirectory* addr_space = create_address_space();
        map_kernel(addr_space);
        switch_dir(addr_space);
        for(int i = 0; i < size; i += 4096)
        {
            void* block = alloc_block();
            map_address(addr_space, (uint32_t)base + i, (uint32_t)block, PTE_PRESENT | PTE_WRITEABLE | PTE_USER);
            memcpy((void*)base + i, buffer + i, 4096);
        }
        void* stack_phys = alloc_block();
        map_address(addr_space, base + size, (uint32_t)stack_phys, PTE_PRESENT | PTE_WRITEABLE | PTE_USER);
        void* stack_virt = (void*)base + size;
        stack = (int)stack_virt + 4096;
        disable();
        process* proc = create_process(addr_space, 1, base, size);
        create_thread((void*)aentry, proc->pid, 0, 1, 0, stack_virt);
        enable();
    }
}

void sys_exit(int pid)
{
    int i;
    process* proc = find_proc(pid);
    process* parent = proc->parent;
    disable();
    for(i = 0; i <= proc->num_used_threads; i++)
    {
        destroy_thread(proc->threads[i], 0);
        disable();
    }
    int num_blocks = proc->image_size / 4096;
    for(i = 0; i < num_blocks; i++)
    {
        uint32_t virt = (i * 4096) + proc->image_base;
        uint32_t block = (uint32_t)get_physical_address(proc->p_dir, virt);
        // Warning: This is an ugly hack to work around a problem in get_physical_address
        if((block & 0xFFFFF000))
        {
            block &= 0xFFFFF000;
            block += 0x1000;
        }
        block -= 4096;
        free_block((void*)block);
    }
    parent->return_value = proc->return_value;
    if(get_list_front()->pid != proc->pid)
        delete_process(proc);
    else
        delete_front_proc();
    enable();
    for(;;);
}

int sys_fork(int tid)
{
    disable();
    thread* to_copy = find_thread(tid);
    process* to_fork = find_proc(to_copy->owning_pid);
    pdirectory* addr_space = create_address_space();
    map_address_space(addr_space, to_fork->p_dir);
    process* new_proc = create_process(addr_space, to_fork->pid, to_fork->image_base, to_fork->image_size);
    regs* state = get_regs();
    thread* new_thread = create_thread((void*)state->eip, new_proc->pid, 0, to_copy->tid, 0, to_copy->stack);
    new_thread->regs.eflags = state->eflags;
    new_thread->regs.eax = 0;
    new_thread->regs.esp = state->useresp;
    new_thread->regs.ebx = state->ebx;
    new_thread->regs.ecx = state->ecx;
    new_thread->regs.edx = state->edx;
    new_thread->regs.esi = state->esi;
    new_thread->regs.edi = state->edi;
    new_thread->regs.ebp = state->ebp;
    enable();
    return new_proc->pid;
}


