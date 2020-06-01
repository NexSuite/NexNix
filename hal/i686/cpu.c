/*
    cpu.c - contains CPU driver implemenation
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifdef ARCH_X86
#include <stdint.h>
#include <stddef.h>
#include <kernel/kernel.h>
#include <kernel/system.h>
#include <kernel/init.h>
#include "../hal-i386.h"
#include "include/cpu.h"

int cpu_init()
{
    init_gdt();
    init_idt();
    pit_init();
    return SUCCESS;
}

void enable()
{
    asm("sti");
}

void disable()
{
    asm("cli");
}

#endif
