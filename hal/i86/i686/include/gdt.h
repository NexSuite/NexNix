/*
    gdt.h - contains GDT functions and structures
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifndef _GDT_H
#define _GDT_H

typedef struct _gdt_entry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
}__attribute__((packed)) gdt_entry_t;

typedef struct _gdt_ptr
{
    uint16_t limit;
    uint32_t base;
}__attribute__((packed)) gdt_ptr_t;

#define MAX_DESCRIPTORS 6

void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

#endif
