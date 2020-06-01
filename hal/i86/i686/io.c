/*
    io.c - has low lever I/O functions
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifdef ARCH_X86
#include <stdint.h>
#include <stddef.h>
#include <kernel/kernel.h>

void outb_internal(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

uint8_t inb_internal(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                 : "=a"(ret)
                 : "Nd"(port) );
    return ret;
}

void outw_internal(uint16_t port, uint16_t val)
{
    asm volatile ( "outw %0, %1" : : "a"(val), "Nd"(port) );
}

uint16_t inw_internal(uint16_t port)
{
    uint16_t ret;
    asm volatile ( "inw %1, %0"
                 : "=a"(ret)
                 : "Nd"(port) );
    return ret;
}

#endif
