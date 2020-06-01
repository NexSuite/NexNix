/*
    terminal.h - contains terminal definitions
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifndef _KERNEL_TERMINAL_H
#define _KERNEL_TERMINAL_H

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

void terminal_init();
void terminal_write_char(char c);
void terminal_print_string(char* s);
void terminal_set_color(enum vga_color fg, enum vga_color bg);
void terminal_clear_screen();

#endif
