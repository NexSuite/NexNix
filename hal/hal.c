/*
    hal.c - contains hal interface
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifdef ARCH_X86
#include <stdint.h>
#include <stdio.h>
#include <kernel/kernel.h>
#include <kernel/multiboot.h>
#include <kernel/init.h>
#include "hal-i386.h"

int hal_init(multiboot_info* bootinfo, uint32_t rd_end)
{
    serial_write_string("[hal] hal initialization started.\r\n");
    int ret = cpu_init();
    if(ret != SUCCESS)
        return GENERAL_ERROR;
    serial_write_string("[hal] CPU state setup successfully.\r\n");
    init_allocator(bootinfo, rd_end);
    vmm_init();
    rtc_init();
    serial_write_string("[hal] HAL initialized successfully.\r\n");
    return SUCCESS;
}

#endif
