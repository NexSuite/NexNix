/*
    terminal.h - contains terminal definitions
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifndef _TERMINAL_H
#define _TERMINAL_H

#define VGA_CMD 0x3D4
#define VGA_DATA 0x3D5
#define VGA_CURSOR_HIGH 15
#define VGA_CURSOR_LOW 14
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_TEXTMEM 0xB8000

uint16_t vga_make_entry(char c, uint8_t color);
uint8_t vga_set_color(enum vga_color fg, enum vga_color bg);
void vga_write_reg(uint16_t port, uint8_t data);
uint8_t vga_read_reg(uint8_t port);
void vga_move_csr(int x, int y);

typedef struct _terminal_info
{
    uint32_t width;
    uint32_t height;
    uint32_t max_row;
    uint32_t max_col;
    uint32_t color;
    uint32_t row;
    uint32_t col;    
}terminal_info;


#endif
