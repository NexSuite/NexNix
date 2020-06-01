/*
    io.c - has libc io functions
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdint.h>
#include <kernel/system.h>
#include <sys/io.h>

void outb(uint16_t port, uint8_t val)
{
    outb_internal(port, val);
}

uint8_t inb(uint16_t port)
{
    return inb_internal(port);
}

void outw(uint16_t port, uint16_t val)
{
    outb_internal(port, val);
}

uint16_t inw(uint16_t port)
{
    return inw_internal(port);
}
