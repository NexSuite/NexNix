/*
    memory.c - contains physical frame allocator
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <kernel/kernel.h>
#include <kernel/system.h>
#include <kernel/multiboot.h>
#include <stdio.h>
#include "../hal-i386.h"

#define MEMMAP_SIZE 131072

uint32_t* mem_map;
uint32_t num_blocks;
uint32_t total_mem;
uint32_t used_blocks;

void mmap_set(int block)
{
     mem_map[block / 32] |= (1 << (block % 32));
}

void mmap_unset(int block)
{
     mem_map[block / 32] &= (1 << (block % 32));
}

int mmap_test(int block)
{
     return mem_map[block / 32] & (1 << (block % 32));
}

int mmap_first_free()
{
    for (uint32_t i = 0; i < num_blocks / 32; i++)
    {
        if(mem_map[i] != 0xffffffff)
        {
            for(uint32_t j = 0; j < 32; j++)
            {
                int bit = 1 << j;
                if(!(mem_map[i] & bit))
                {
                    return i * 32 + j;
                }
            }
        }
    }
    return -1;
}

int mmap_first_free_s(uint32_t size)
{
    if(size == 0)
        return -1;
    if(size == 1)
        return mmap_first_free();

    for (uint32_t i = 0; i < used_blocks / 32; i++)
    {
        if(mem_map[i] != 0xffffffff)
        {
            for(uint32_t j = 0; j < 32; j++)
            {
                  int bit = 1 << j;
                  if(!(mem_map[i] & bit))
                  {
                      int start = i * 32;
                      start += bit;
                      uint32_t free = 0;
                      for (uint32_t count = 0; count <= size; count++)
                      {
                          if(!mmap_test(start + count))
                          {
                              free++;
                          }
                          if(free == size)
                          {
                              return i * 32 + j;
                          }
                      }
                  }
            }
        }
    }
    return -1;
}

void init_region(int base, int size)
{
    int align = base / 4096;
    int block = size / 4096;

    for(; block > 0; block--)
    {
        mmap_unset(align++);
        used_blocks--;
    }
    mmap_set(0);
}

void deinit_region(int base, int size)
{
    int align = base / 4096;
    int block = size / 4096;

    for(; block > 0; block--)
    {
        mmap_set(align++);
        used_blocks++;
    }
}

void* alloc_block()
{
    if((num_blocks - used_blocks) == 0)
        return 0;
    int frame = mmap_first_free();
    mmap_set(frame);
    used_blocks++;
    int base = frame * 4096;
    return (void*)base;
}

void free_block(void* p)
{
    int addr = (int)p;
    int frame = addr / 4096;
    mmap_unset(frame);
    used_blocks--;
}

void* alloc_blocks(int num)
{
    if((num_blocks - used_blocks) == 0)
        return 0;
    if(num == 0)
        return 0;
    if(num == 1)
        return alloc_block();
    int frame = mmap_first_free_s(num);
    for(int i = 0; i < num; i++)
        mmap_set(frame + i);
    used_blocks += num;
    int base = frame * 4096;
    return (void*)base;
}

void free_blocks(void* p, int num)
{
    int base = (int)p;
    int frame = base / 4096;
    for(int i = 0; i < num; i++)
        mmap_unset(frame + i);
    used_blocks -= num;
}

void init_allocator(multiboot_info* bootinfo, uint32_t rd_end)
{
    total_mem = bootinfo->memLower = bootinfo->memUpper + 1024;
    serial_printf("[pmm] PMM initializing with %d bytes of memory\r\n", total_mem);
    num_blocks = (total_mem * 1024) / 4096;
    used_blocks = 0;
    mem_map = (uint32_t*)kmalloc(MEMMAP_SIZE);
    memset(mem_map, 0xff, MEMMAP_SIZE);
    mmap_entry* mmap = (mmap_entry*)bootinfo->memMapAddress;
	mmap_entry* mmap_end = (mmap_entry*)(bootinfo->memMapAddress + bootinfo->memMapLength);
    while(mmap < mmap_end)
    {
        if(mmap->type == 1)
        {
            init_region(mmap->base_addr, mmap->length);
        }
        mmap = (mmap_entry*)((uint32_t)mmap + mmap->length + sizeof(mmap->length));
    }
    deinit_region(0xC0000000, 0xFFFFFFFF);
    serial_printf("[pmm] PMM initialized.\r\n");
}
