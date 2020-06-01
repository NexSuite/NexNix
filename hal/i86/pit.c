/*
    pit.c - contains PIT minidriver
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifdef ARCH_X86
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <kernel/kernel.h>
#include <kernel/api.h>
#include <kernel/system.h>
#include <stdio.h>
#include <sys/io.h>
#include "../hal-i386.h"

volatile unsigned long long ticks = 0;

void pit_tick(regs* r)
{
    ++ticks;
    if(sys_event_find(ticks))
    {
        sys_event_broadcast(ticks, 0);
    }
}

void pit_init()
{
    irq_install_handler(0, (void*)&pit_tick);
    uint32_t divisor = 1193180 / 50;
    outb(0x43, 0x36);
    uint8_t lower = (uint8_t)(divisor & 0xFF);
    uint8_t higher = (uint8_t)( (divisor >> 8) & 0xFF );
    outb(0x40, lower);
    outb(0x40, higher);
    serial_write_string("[hal] PIT initalized at IRQ 0.\r\n");
}

void wait(uint64_t num_ticks)
{
    if(sys_event_find(ticks + num_ticks))
    {
        sys_event_join(ticks + num_ticks);
    }
    else
    {
        sys_event_create(ticks + num_ticks);
        sys_event_join(ticks + num_ticks);
    }
    sys_event_delete(ticks + num_ticks);
}

#endif
