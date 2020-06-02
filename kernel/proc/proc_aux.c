/*
    proc_aux.c - contains auxillary tasker functions
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <kernel/kernel.h>
#include <kernel/system.h>
#include <kernel/tasking.h>
#include <kernel/api.h>

int num_used_des = 0;

int sys_get_tid()
{
    return get_queue_front()->tid;
}

int sys_get_pid()
{
    return get_queue_front()->owning_pid;
}

void set_working_directory(int tid, char* path)
{
    thread* target = find_thread(tid);
    if(path[0] == '/')
        strcpy(target->working_dir, path);
    else
        strcat(target->working_dir, path);
}

char* get_working_directory(int tid)
{
    return find_thread(tid)->working_dir;
}

void* sys_sbrk(int num)
{
    process* proc = find_proc(get_queue_front()->owning_pid);
    void* block = alloc_page(get_directory(), proc->max_addr, 1);
    proc->max_addr += PAGE_SIZE;
    if(num == 1)
        return block;
    for(int i = 0; i <= (num - 1); i++)
    {
        alloc_page(get_directory(), proc->max_addr, 1);
        proc->max_addr += 4096;
    }
    return block;
}

void* sys_brk()
{
    return sys_sbrk(1);
}
