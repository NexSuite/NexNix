/*
    kernel.h - contains kernel specific non POSIX NexNix kernel functions
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifndef _KERNEL_KERNEL_H
#define _KERNEL_KERNEL_H
#include "../stdint.h"
#include "multiboot.h"
#define PANIC(str) \
                    panic(str); \
                    printf("\nin file "); \
                    printf(__FILE__); \
                    printf(" on line "); \
                    printf("%d\n", __LINE__); \
                    abort();

void panic(const char* str);
void serial_write_char(char c);
void serial_write_string(char* s);
char* serial_read_string();
void parallel_write_char(char c);
void parallel_write_string(char* s);
uint32_t kmalloc_a(uint32_t sz);
uint32_t kmalloc(uint32_t sz);
void* krealloc(int size, void* p, int diff);
void kfree(void* p);
void* kcache(void* p, size_t sz);
void* kdecache(void* p);
void* kget_cache_object();
void* read_file(char* name, int* size);
void load_initrd(int size);

void video_put_pixel(int x, int y, uint32_t color);
void video_rect(int x, int y, uint32_t color, int width, int height);
void video_put_char(int x, int y, uint32_t fg, char c);
void video_put_string(int x, int y, uint32_t fg, char* s);
uint32_t video_get_width();
uint32_t video_get_height();

void serial_driver_init();

int serial_printf(char* restrict str, ...);

#endif
