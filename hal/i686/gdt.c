/*
    gdt.c - contains GDT code
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
#include "../hal-i386.h"
#include "include/gdt.h"
#include "include/cpu.h"

gdt_entry_t _gdt[MAX_DESCRIPTORS];
gdt_ptr_t ptr;
extern void gdt_flush();

void init_gdt()
{
    ptr.limit = (sizeof(gdt_entry_t) * MAX_DESCRIPTORS) - 1;
    ptr.base = (uint32_t)&_gdt;
    gdt_set_gate(0, 0, 0, 0, 0);
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
    gdt_flush();
    serial_write_string("[hal] GDT initialized.\r\n");
    int stack = 0;
    asm("mov %%esp, %0" : "=r"(stack));
    tss_install(5, 0x10, stack);
    serial_write_string("[hal] TSS initialized.\r\n");
}

void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    _gdt[num].base_low = (base & 0xFFFF);
    _gdt[num].base_mid = (base >> 16) & 0xFF;
    _gdt[num].base_high = (base >> 24) & 0xFF;
    _gdt[num].limit_low = (limit & 0xFFFF);
    _gdt[num].granularity = ((limit >> 16) & 0x0F);
    _gdt[num].granularity |= (gran & 0xF0);
    _gdt[num].access = access;
}

#endif
