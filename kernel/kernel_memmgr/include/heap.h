/*
    heap.h - contains kernel heap back end interface
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifndef _HEAP_H
#define _HEAP_H

#include <stddef.h>
#include <stdint.h>

#define HEAP_HEADER_BASE 0xC0400000
#define HEAP_BASE 0xC0450000
#define HEAP_MAX 0xC0350000
#define HEAP_MAX_SIZE (HEAP_MAX - 0xC0000000)
#define HEAP_INITIAL_SIZE 0x200
#define MAGIC 0xDEADBEEF

typedef struct _header
{
    uint32_t magic;
    uint32_t base;
    uint32_t size;
    int isFree;
    int isLast;
    int isUsable;
}header;

typedef struct _heap
{
    header* heapLayout;
    int num;
    uint32_t base;
    uint32_t max_size;
    uint32_t size;
    int magic;
}heap;

#endif
