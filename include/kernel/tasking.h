/*
    tasking.h - contains multitasking structures
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifndef _TASKING_H
#define _TASKING_H

#include <stdint.h>
#include <kernel/kernel.h>
#include <kernel/vfs.h>
#include <kernel/api.h>

#define THREAD_STATE_RUNNING 1
#define THREAD_STATE_SPAWNING 0
#define THREAD_STATE_STOPPING -1
#define THREAD_STATE_SLEEPING 2
#define THREAD_STATE_ACTIVE 3
#define THREAD_STATE_SLEEP_SPAWNING 4

typedef struct _trap_frame
{
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t edi;
    uint32_t esi;
    uint32_t esp;
    uint32_t ebp;
    uint32_t eip;
    uint32_t eflags;
    uint32_t cr3;
    uint16_t ds;
    uint16_t es;
    uint16_t fs;
    uint16_t gs;
    uint16_t ss;
    uint16_t cs;
}trap_frame;

typedef struct _thread
{
    struct _thread* parent;
    int owning_pid;
    int tid;
    int time_reminaing;
    int state;
    int is_kernel;
    uint32_t stack;
    int stack_size;
    uint32_t kernel_stack;
    int kernel_stack_size;
    int return_value;
    int first_run;
    int sleep_delta;
    char* working_dir;
    trap_frame regs;
    struct _thread* next;
}thread;

typedef struct _process
{
    struct _process* parent;
    int threads[36];
    int num_used_threads;
    int pid;
    uint32_t max_addr;
    int return_value;
    pdirectory* p_dir;
    uint32_t pdbr;
    long long image_base;
    long long image_size;
    struct _process* next;
}process;


#define TASK_QUANTAM 3

void init_queue();

void add_to_front(thread* thread);

thread* add_to_back(thread* athread);

thread* get_queue_front();

thread* alloc_thread();

thread* switch_thread();

thread* find_thread(int tid);

int alloc_tid();

void delete_thread(thread* dthread);

process* alloc_process();

int alloc_pid();

process* find_proc(int pid);

void delete_process(process* proc);

thread* create_thread(void* thread_func, int owning_pid, int is_kernel, int creator, int is_init, void* user_stack);

process* create_process(pdirectory* p_dir, int parent_pid, uint32_t base, uint32_t size);

void delete_front_proc();

process* get_list_front();

void sys_open_file(vfs_file* file, int* file_des, int flags, int tid);

char* get_working_directory(int tid);

void set_working_directory(int tid, char* path);

void remove_thread(thread* dthread);

void delete_sleeping_thread(thread* dthread);

thread* find_sleeping_thread(int tid);

void add_sleeping_thread(thread* thread);

void remove_front();

#endif
