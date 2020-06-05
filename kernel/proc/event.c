/*
    event.c - contains kernel event system
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdint.h>
#include <kernel/system.h>
#include <kernel/kernel.h>
#include <kernel/api.h>
#include <kernel/tasking.h>
#include <kernel/init.h>
#include <kernel/event.h>

event** events;

void event_init()
{
    events = (event**)kmalloc(sizeof(event) * 128);
    memset(events, 0, sizeof(event));
}

void sys_event_create(int event)
{
    int i = 0;
    while(events[i] != 0)
    {
        i++;
        if(i == 128)
            return;
    }
    events[i] = kmalloc(sizeof(event));
    events[i]->id = event;
}

void sys_event_delete(int event)
{
    int i = 0;
    while(events[i]->id != event)
    {
        i++;
        if(i == 128)
            return;
    }
    events[i] = 0;
}

int sys_event_broadcast(int event, int save)
{
    int i = 0;
    while(events[i]->id != event)
    {
        i++;
        if(i == 128)
            return -1;
    }
    disable();
    thread* main = get_queue_front();
    for(int j = 0; j < events[i]->num_joined; i++)
    {
        thread* thread = find_sleeping_thread(events[i]->joined[j]);
        delete_sleeping_thread(thread);
        add_to_front(thread);
        thread->state = THREAD_STATE_ACTIVE;
        thread->first_run = 1;
    }
    if(save)
    {
        main->regs.cs = get_cs();
        main->regs.ds = get_ds();
        main->regs.es = get_es();
        main->regs.fs = get_fs();
        main->regs.gs = get_gs();
        main->regs.ss = get_ss();

        main->regs.eax = get_eax();
        main->regs.ebx = get_ebx();
        main->regs.ecx = get_ecx();
        main->regs.edx = get_edx();
        main->regs.esi = get_esi();
        main->regs.edi = get_edi();

        main->regs.eflags = get_eflags();
        main->regs.esp = get_esp();
        main->regs.ebp = get_ebp();
        main->regs.eip = get_eip();
    }

    asm("sti");
    asm("int $32");         // Force a task switch
    return 0;
}

int sys_event_find(int event)
{
    for(int i = 0; i < 128; i++)
    {
        if(events[i]->id == event)
            return 1;
    }
    return 0;
}

int sys_event_join(int event)
{
    int i = 0;
    while(events[i]->id != event)
    {
        i++;
        if(i == 128)
            return -1;
    }
    int j = 0;
    while(events[i]->joined[j] != 0)
    {
        j++;
        if(j == 60)
            return -1;
    }
    events[i]->joined[j] = sys_get_tid();
    events[i]->num_joined++;
    int tid = sys_get_tid();
    disable();
    thread* block = find_thread(sys_get_tid());

    if(!block)
    {
        enable();
        return -1;
    }

    remove_front();
    add_sleeping_thread(block);
    block->state = THREAD_STATE_SLEEPING;

    block->regs.cs = get_cs();
    block->regs.ds = get_ds();
    block->regs.es = get_es();
    block->regs.fs = get_fs();
    block->regs.gs = get_gs();
    block->regs.ss = get_ss();

    block->regs.eax = get_eax();
    block->regs.ebx = get_ebx();
    block->regs.ecx = get_ecx();
    block->regs.edx = get_edx();
    block->regs.esi = get_esi();
    block->regs.edi = get_edi();

    block->regs.eflags = get_eflags();
    block->regs.esp = get_esp();
    block->regs.ebp = get_ebp();
    asm("sti");
    block->regs.eip = get_eip();
    while(get_queue_front()->tid != tid) serial_write_string(" \b");

    return 0;
}