/*
    driver_core.h - contains driver framework functions
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifndef _DRIVER_CORE_H
#define _DRIVER_CORE_H

#define NUM_CORE 3

#define STATE_RUNNING 1
#define STATE_STOPPED 0
#define STATE_SUSPEND 2

void install_driver(int id, void* init_function);
void uninstall_driver(int id);

void set_driver_status(int id, int status);
int get_driver_status(int id);

void set_status_handler(int id, int status, void* funct);
void* get_status_handler(int id, int status);

#define DRIVER_TERMINAL 0
#define DRIVER_SERIAL 1
#define DRIVER_PARALLEL 2
#define DRIVER_VIDEO 3

#endif
