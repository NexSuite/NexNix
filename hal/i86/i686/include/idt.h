/*
    idt.h - contains IDT functions and structures
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/
#ifndef _IDT_H
#define _IDT_H

typedef struct _idt_entry
{
    uint16_t base_low;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_high;
}__attribute__((packed)) idt_entry_t;

typedef struct _idt_ptr
{
    uint16_t limit;
    uint32_t base;
}__attribute__((packed)) idt_ptr_t;

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
void install_isrs();
void irqs_init();

#endif
