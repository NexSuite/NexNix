/*
    api.h - contains kernel api calls
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifndef _KERNEL_API_H
#define _KERNEL_API_H

int sys_fork(int tid);
int sys_get_tid();
int sys_get_pid();

int sys_event_join(int event);
int sys_event_find(int event);
int sys_event_broadcast(int event, int save);
void sys_event_delete(int event);
void sys_event_create(int event);

int sys_create_thread(void* func, void* data, int priority);

#endif
