/*
    cache.h - contains backend cache interface
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifndef _CACHE_H
#define _CACHE_H

#include <stdint.h>

#define CACHE_HEADER_BASE 0xC0800000
#define CACHE_BASE 0xC0850000
#define CACHE_MAX 0x00350000
#define CACHE_INITIAL_SIZE 0x200
#define MAGIC 0xDEADBEEF

typedef struct _header
{
    uint32_t magic;
    uint32_t base;
    uint32_t heap_base;
    uint32_t size;
    int isFree;
    int isLast;
    int isSwapped;
    int isUsable;
}header;

typedef struct _cache
{
    header* cacheLayout;
    int num;
    uint32_t base;
    uint32_t max_size;
    uint32_t size;
    int magic;
}cache;

#endif
