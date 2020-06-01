/*
    init.h - contains initialization functions and error codes
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifndef _KERNEL_INIT_H
#define _KERNEL_INIT_H

#include "multiboot.h"

int init(multiboot_info* bootinfo, uint32_t magic);
int hal_init(multiboot_info* bootinfo, uint32_t kernel_end);
void vmm_init();
void serial_init();
void parallel_init();
void terminal_init();
void video_init();
void init_kernel_heap();
void init_kernel_cache();
void rtc_init();
void init_initrd(uint32_t addr);
void sysapi_init(int num);
void start_driver_framework();
void scheduler_init();
void serial_init();
void event_init();

#define SUCCESS 0
#define INVALID_MULTIBOOT -1
#define GENERAL_ERROR 1

#endif
