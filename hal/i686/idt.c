/*
    idt.c - contains IDT implementation
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifdef ARCH_X86
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <kernel/kernel.h>
#include <kernel/system.h>
#include <stdio.h>
#include "../hal-i386.h"
#include "include/idt.h"
#include "include/cpu.h"

idt_entry_t _idt[256];
idt_ptr_t iptr;
extern void idt_flush();

__attribute__((naked)) void def_handler()
{
    PANIC("Unhandled Interrupt");
    asm("cli; hlt;");
}

void init_idt()
{
    iptr.limit = (sizeof(idt_entry_t) * 256) - 1;
    iptr.base = (uint32_t)&_idt;
    memset(&_idt, 0, 256 * sizeof(idt_entry_t));
    for(int i = 0; i < 256; i++)
    {
        idt_set_gate(i, (unsigned)def_handler, 0x08, 0x8E);
    }
    idt_flush();
    serial_write_string("[hal] IDT initialized.\r\n");
    install_isrs();
    serial_write_string("[hal] Exception handlers installed.\r\n");
    irqs_init();
    serial_write_string("[hal] IRQs initialized.\r\n");
}

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    _idt[num].base_low = (base & 0xFFFF);
    _idt[num].base_high = (base >> 16) & 0xFFFF;
    _idt[num].sel = sel;
    _idt[num].always0 = 0;
    _idt[num].flags = flags | 0x60;
}

#endif
