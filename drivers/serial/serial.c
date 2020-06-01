/*
    serial.c - contains serial driver
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <kernel/kernel.h>
#include <kernel/system.h>
#include <kernel/driver_core.h>
#include <sys/io.h>
#include "serial.h"

char current_char = 0;
int irq = 0;

void serial_irq(regs* r)
{
    current_char = inb(SERIAL_BASE);
    irq = 1;
}

void serial_init()
{
    outb(SERIAL_BASE + 1, 0x00);
    outb(SERIAL_BASE + 3, 0x80);
    outb(SERIAL_BASE + 0, 0x03);
    outb(SERIAL_BASE + 1, 0x00);
    outb(SERIAL_BASE + 3, 0x03);
    outb(SERIAL_BASE + 2, 0xC7);
    outb(SERIAL_BASE + 4, 0x0B);
    outb(SERIAL_BASE + 1, 0x80);
    //irq_install_handler(4, serial_irq);
}

void serial_driver_init()
{
    set_status_handler(DRIVER_SERIAL, STATE_RUNNING, serial_init);
}

int is_empty()
{
    return inb(SERIAL_BASE + 5) & 0x20;
}

void serial_write_char(char c)
{
    while(is_empty() == 0)
    {
        continue;
    }
    outb(SERIAL_BASE, c);
}

void serial_write_string(char* s)
{
    for(int i = 0; i < (int)strlen(s); i++)
        serial_write_char(s[i]);
}

char serial_read_char()
{
    while(!irq) continue;
    irq = 0;
    return current_char;
}

char* serial_read_string()
{
    char buffer[255];
    int i = 0;
    char c = serial_read_char();
    while(c != '\n')
    {
        buffer[i] = c;
        i++;
        c = serial_read_char();
    }
    buffer[i] = '\0';
    return (char*)buffer;
}
