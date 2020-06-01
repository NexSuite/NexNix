/*
    tss.c - contains TSS routines
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdint.h>
#include <string.h>
#include <kernel/kernel.h>
#include <kernel/system.h>
#include "include/gdt.h"
#include "include/tss.h"

static tss_entry tss;

extern void tss_flush();

void tss_install(uint32_t idx, uint16_t kernelSS, uint64_t kernelESP)
{
    uint32_t base = (uint32_t) &tss;
    gdt_set_gate(idx, base, base + sizeof(tss_entry), 0xE9, 0x00);
    memset(&tss, 0, sizeof(tss_entry));
    tss.ss0 = kernelSS;
    tss.esp0 = kernelESP;
    tss.cs = 0x0b;
    tss.ss = tss.ds = tss.es = tss.fs = tss.gs = 0x13;
    tss.iomap = sizeof(tss_entry);
    tss_flush();
}

void tss_set_stack(uint16_t kernelSS, uint32_t kernelESP)
{
    tss.ss0 = kernelSS;
    tss.esp0 = kernelESP;
}
