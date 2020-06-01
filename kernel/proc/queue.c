/*
    queue.c - contains queue functions
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdint.h>
#include <kernel/system.h>
#include <kernel/kernel.h>
#include <kernel/tasking.h>

process* proc_list;
thread* ready_queue;
thread* sleeping_queue;

int num_tid_allocs = 0;

void init_queue()
{
    proc_list = 0;
    ready_queue = 0;
    sleeping_queue = 0;
}

void add_to_front(thread* thread)
{
    thread->next = ready_queue;
    ready_queue = thread;
}

thread* add_to_back(thread* athread)
{
    thread* iterator = ready_queue;
    while(iterator->next != 0)
    {
        iterator = iterator->next;
    }
    iterator->next = athread;
    athread->next = 0;
    return iterator->next;
}

thread* get_queue_front()
{
    return ready_queue;
}

thread* alloc_thread()
{
    thread* new = (thread*)kmalloc(sizeof(thread));
    add_to_back(new);
    return new;
}

thread* alloc_init_thread()
{
    thread* new = (thread*)kmalloc(sizeof(thread));
    add_to_front(new);
    return new;
}

thread* switch_thread()
{
    thread* temp = ready_queue;
    ready_queue = ready_queue->next;
    return add_to_back(temp);
}

thread* find_thread(int tid)
{
    thread* iterator = ready_queue;
    while(iterator->tid != tid && iterator != 0)
        iterator = iterator->next;
    return iterator;
}

void add_sleeping_thread(thread* thread)
{
    thread->next = sleeping_queue;
    sleeping_queue = thread;
}

thread* find_sleeping_thread(int tid)
{
    thread* iterator = sleeping_queue;
    while(iterator->tid != tid && iterator != 0)
        iterator = iterator->next;
    return iterator;
}

void delete_sleeping_thread(thread* dthread)
{
    thread* iterator = sleeping_queue;
    while(iterator->next != dthread && iterator != 0)
        iterator = iterator->next;
    thread* replace = dthread->next;
    iterator->next = replace;
}

int alloc_tid()
{
    return ++num_tid_allocs;
}

void remove_thread(thread* dthread)
{
    thread* iterator = ready_queue;
    while(iterator->next != dthread && iterator != 0)
        iterator = iterator->next;
    thread* replace = dthread->next;
    iterator->next = replace;
}

void remove_front()
{
    ready_queue = ready_queue->next;
}

void delete_thread(thread* dthread)
{
    remove_thread(dthread);
    kfree(dthread);
}

void delete_front()
{
    thread* temp = ready_queue;
    ready_queue = ready_queue->next;
    kfree(temp);
}

int num_pid_allocs = 0;

process* alloc_process()
{
    process* new = (process*)kmalloc(sizeof(process));
    new->next = proc_list;
    proc_list = new;
    return new;
}

int alloc_pid()
{
    return ++num_pid_allocs;
}

process* find_proc(int pid)
{
    process* iterator = proc_list;
    while(iterator->pid != pid)
        iterator = iterator->next;
    return iterator;
}

void delete_front_proc()
{
    process* temp = proc_list;
    proc_list = proc_list->next;
    kfree(temp);
}

process* get_list_front()
{
    return proc_list;
}

void delete_process(process* proc)
{
    process* iterator = proc_list;
    while(iterator->next != proc)
    {
        iterator = iterator->next;
    }
    process* replace = proc->next;
    iterator->next = replace;
    kfree(proc);
}
