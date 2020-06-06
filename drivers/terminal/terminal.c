/*
    terminal.c - contains high level terminal routines
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <kernel/kernel.h>
#include <kernel/system.h>
#include <kernel/terminal.h>
#include <kernel/driver_core.h>
#include <kernel/api.h>
#include "terminal.h"

int term_lock = 0;

terminal_info term_info;

void terminal_write_char(char c)
{
    sys_acquire(&term_lock);
    if(c == '\n')
    {
        term_info.row++;
        term_info.col = 0;
        if(term_info.row == term_info.max_row)
        {
            video_scroll();
            term_info.row = term_info.max_row - 1;
            term_info.col = 0;
        }
        return;
    }
    video_put_char(term_info.col * 8, term_info.row * 8, term_info.color, c);
    term_info.col++;
    if(term_info.col == term_info.max_col)
    {
        term_info.row++;
        if(term_info.row == term_info.max_row)
        {
            video_scroll();
            term_info.row = term_info.max_row;
            term_info.col = 0;
            return;
        }
    }
    sys_release(&term_lock);
}

void terminal_print_string(char* s)
{
    for(int i = 0; i < strlen(s); i++)
        terminal_write_char(s[i]);
}

void terminal_data_init()
{
    term_info.color = 0x00DCDCDC;
    term_info.height = video_get_height();
    term_info.width = video_get_width();
    term_info.max_col = video_get_width() / 8;
    term_info.max_row = video_get_height() / 8;
}

void terminal_init()
{
    set_status_handler(DRIVER_TERMINAL, STATE_RUNNING, terminal_data_init);
}

/*void terminal_clear_screen()
{
    col = row = 0;
    int x, y;
    for(x = 0; x < VGA_WIDTH; x++)
    {
        for(y = 0; y < VGA_HEIGHT; y++)
        {
            int location = y * VGA_WIDTH + x;
            buffer[location] = vga_make_entry(' ', color);
        }
    }
    vga_move_csr(col, row);
}

void terminal_scroll()
{
    char space = vga_make_entry(' ', color);
    if(row >= 25)
    {
        int i = 0;
        for(i = 0; i < 80 * 24; i++)
        {
            buffer[i] = buffer[i + 80];
        }
        for(i = 80 * 24; i < 25 * 80; i++)
        {
            buffer[i] = space;
        }
        row = 24;
    }
}

void terminal_put(char c)
{
    const size_t index = row * VGA_WIDTH + col;
    buffer[index] = vga_make_entry(c, color);
}

void terminal_write_char(char c)
{
    if(c == '\n')
    {
        row++;
        col = 0;
        terminal_scroll();
        return;
    }
    terminal_put(c);
    if(++col == VGA_WIDTH)
    {
        col = 0;
        if(++row == VGA_HEIGHT)
            row = 0;
    }
    terminal_scroll();
    vga_move_csr(col, row);
}

void terminal_set_color(enum vga_color fg, enum vga_color bg)
{
    color = vga_set_color(fg, bg);
}

void terminal_write_string(char* s)
{
    for(int i = 0; i < (int)strlen(s); i++)
        terminal_write_char(s[i]);
}*/
