/*
    kernel.c - contains the main kernel function
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <kernel/kernel.h>
#include <kernel/system.h>
#include <kernel/multiboot.h>
#include <kernel/terminal.h>
#include <kernel/init.h>
#include <stdio.h>
#include <stdlib.h>

void kernel_main(multiboot_info* bootinfo, uint32_t magic)
{
    serial_init();
    serial_write_string("[kernel] Kernel booted.\r\n");
    int ret = init(bootinfo, magic);
    if(ret == GENERAL_ERROR)
    {
        PANIC("An error occurred during startup!");
        exit(GENERAL_ERROR);
    }
    if(ret == INVALID_MULTIBOOT)
    {
        PANIC("Invalid Multiboot!");
        exit(INVALID_MULTIBOOT);
    }
    //exit(EXIT_SUCCESS);
    for(;;);
}
