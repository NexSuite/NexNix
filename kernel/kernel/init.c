/*
    init.c - initializes system
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdint.h>
#include <stdio.h>
#include <kernel/kernel.h>
#include <kernel/init.h>
#include <kernel/system.h>
#include <kernel/tasking.h>
#include <kernel/multiboot.h>
#include <kernel/vfs.h>

void kernel_init_thread();
void event_thread();
void ithread();

multiboot_info* info = 0;

int init(multiboot_info* bootinfo, uint32_t magic)
{
    info = bootinfo;
    multiboot_module* initrd = (multiboot_module*)bootinfo->moduleAddress;
    init_initrd(initrd[0].mod_start);
    load_initrd(initrd[0].mod_end - initrd[0].mod_start);
    hal_init(bootinfo, 0);
    serial_write_string("[kmem] Starting kernel memory manager\r\n");
    init_kernel_cache();
    init_kernel_heap();
    start_driver_framework();
    printf("Starting NexNix...\n");
    if(magic != MULTIBOOT_BOOTLOADER_MAGIC)
        return INVALID_MULTIBOOT;
    if(bootinfo->moduleCount == 0)
        return INVALID_MULTIBOOT;
    event_init();
    scheduler_init();
    serial_write_string("[kernel] System started successfully.\r\n");
    create_thread(kernel_init_thread, 1, 1, 1, 1, 0);
    create_thread(event_thread, 1, 1, 2, 0, 0);
    create_thread(ithread, 1, 1, 2, 0, 0);
    enable();
    return SUCCESS;
}

multiboot_info* get_boot_info()
{
    return info;
}


void kernel_init_thread()
{
    for(;;) asm("pause");
}

void ithread()
{
    for(;;);
}

void event_thread()
{
    for(;;) asm("pause");
}
