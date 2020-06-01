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
