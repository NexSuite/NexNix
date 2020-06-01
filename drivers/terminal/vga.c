/*
    vga.c - contains low level video routines
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdint.h>
#include <kernel/kernel.h>
#include <kernel/system.h>
#include <kernel/terminal.h>
#include <sys/io.h>
#include "terminal.h"

uint16_t vga_make_entry(char c, uint8_t color)
{
    return (uint16_t) c | (uint16_t) color << 8;
}

uint8_t vga_set_color(enum vga_color fg, enum vga_color bg)
{
    return fg | bg << 4;
}

void vga_write_reg(uint16_t port, uint8_t data)
{
    outb(port, data);
}

uint8_t vga_read_reg(uint8_t port)
{
    return inb(port);
}

void vga_move_csr(int x, int y)
{
    int location = y * VGA_WIDTH + x;
    vga_write_reg(VGA_CMD, VGA_CURSOR_LOW);
    vga_write_reg(VGA_DATA, location >> 8);
    vga_write_reg(VGA_CMD, VGA_CURSOR_HIGH);
    vga_write_reg(VGA_DATA, location);
}
