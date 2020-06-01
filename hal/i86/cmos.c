/*
    cmos.c - contains CMOS functions
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/
#ifdef ARCH_X86
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <kernel/kernel.h>
#include <kernel/system.h>
#include <kernel/init.h>
#include <sys/io.h>
#include "../hal-i386.h"
#include "include/cmos.h"

void cmos_write_reg(int reg)
{
    outb(CMOS_CMD_REG, (CMOS_NMI_DISABLE << 7) | reg);
}

uint8_t cmos_read()
{
    return inb(CMOS_DATA_REG);
}

int is_144_floppy()
{
    disable();
    cmos_write_reg(CMOS_FLOPPY_REG);
    uint8_t data = cmos_read();
    enable();
    if(data & 0x40)
        return 1;
    return 0;
}

int is_288_floppy()
{
    disable();
    cmos_write_reg(CMOS_FLOPPY_REG);
    uint8_t data = cmos_read();
    enable();
    if(data & 0x50)
        return 1;
    return 0;
}

void nmi_enable()
{
    outb(CMOS_CMD_REG, inb(CMOS_CMD_REG) & 0x7f);
}

void nmi_disable()
{
    outb(CMOS_CMD_REG, inb(CMOS_CMD_REG) | 0x80);
}

#endif
