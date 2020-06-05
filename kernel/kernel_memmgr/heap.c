/*
    heap.c - contains kernel heap code
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <kernel/kernel.h>
#include "include/heap.h"

extern uint32_t end[];
uint32_t address = (uint32_t)end;

heap* kernel_heap;
bool is_heap_init = false;

void init_kernel_heap()
{
    kernel_heap = (heap*)kmalloc(1 * sizeof(kernel_heap));
    is_heap_init = true;
    memset(kernel_heap, 0, sizeof(kernel_heap));
    kernel_heap->max_size = HEAP_MAX_SIZE;
    kernel_heap->heapLayout = (header*)HEAP_HEADER_BASE;
    kernel_heap->size = HEAP_INITIAL_SIZE;
    kernel_heap->base = HEAP_BASE;
    kernel_heap->magic = MAGIC;
    kernel_heap->heapLayout[0].magic = MAGIC;
    serial_printf("got here\r\n");
    kernel_heap->heapLayout[0].base = HEAP_BASE;
    kernel_heap->heapLayout[0].size = 12;
    kernel_heap->heapLayout[0].isFree = 1;
    kernel_heap->heapLayout[0].isLast = 1;
    kernel_heap->heapLayout[0].isUsable = 1;
    kernel_heap->num = 0;
}

void* kernel_heap_alloc(uint32_t size)
{
    if(size < 1)
    {
        return 0;
    }

    for(int i = 0; i < 4096; i++)
    {
        if(kernel_heap->heapLayout[i].isFree == 1)
        {
            if(kernel_heap->heapLayout[i].isUsable == 0)
				        continue;

            if(kernel_heap->heapLayout[i].size == size)
            {
                  kernel_heap->heapLayout[i].isFree = 0;
                  int temp = i;
                  temp++;
                  if(kernel_heap->heapLayout[temp].magic != MAGIC)
                  {
                      kernel_heap->heapLayout[i].isLast = 1;
                  }
                  return (void*) kernel_heap->heapLayout[i].base;
             }
             else if(kernel_heap->heapLayout[i].size > size)
             {
                kernel_heap->heapLayout[i].isFree = 0;
                int differnce = kernel_heap->heapLayout[i].size - size;
                kernel_heap->heapLayout[i].size -= differnce;
                int temp = i;
                temp++;
                if(kernel_heap->heapLayout[temp].magic == MAGIC && kernel_heap->heapLayout[temp].isFree == 1)
                    kernel_heap->heapLayout[temp].base = kernel_heap->heapLayout[temp].base - differnce;
                if(kernel_heap->heapLayout[temp].magic != MAGIC)
                {
                    kernel_heap->heapLayout[i].isLast = 1;
                }
                return (void*) kernel_heap->heapLayout[i].base;
             }
             else
             {
                  int temp = kernel_heap->num;
                  temp++;
                  kernel_heap->heapLayout[temp].magic = MAGIC;
                  kernel_heap->heapLayout[temp].base = kernel_heap->heapLayout[kernel_heap->num].base + kernel_heap->heapLayout[kernel_heap->num].size;
                  kernel_heap->heapLayout[temp].isFree = 0;
                  kernel_heap->heapLayout[temp].isLast = 1;
                  kernel_heap->heapLayout[temp].size = size;
                  kernel_heap->heapLayout[temp].isUsable = 1;
                  kernel_heap->num = temp;
                  kernel_heap->size += size;
                  if(kernel_heap->size >= HEAP_MAX_SIZE)
                  {
                      return (void*)0;
                  }
                  else if((HEAP_MAX_SIZE - kernel_heap->size) <= 0x100)
                  {
                      return (void*)0;
                  }
                  return (void*)kernel_heap->heapLayout[kernel_heap->num].base;
             }
        }
    }
    return 0;
}

void kernel_heap_free(void* p)
{
    if(p == 0)
    {
        return;
    }
    uint32_t base = (uint32_t)p;
    for (int i = 0; i < 4096; i++)
    {
        if(kernel_heap->heapLayout[i].base == base)
        {
            kernel_heap->heapLayout[i].isFree = 1;
            int left, right;
            left = right = i;
            left--;
            right++;
            if(kernel_heap->heapLayout[left].isFree == 1)
            {
                kernel_heap->heapLayout[i].isUsable = 0;
                kernel_heap->heapLayout[left].size += kernel_heap->heapLayout[i].size;
            }
            if(kernel_heap->heapLayout[right].isFree == 1)
            {
                kernel_heap->heapLayout[i].isUsable = 0;
                kernel_heap->heapLayout[right].size += kernel_heap->heapLayout[i].size;
            }
        }
    }
}

uint32_t kmalloc_int(uint32_t sz, int align)
{
    if(!is_heap_init)
    {
        if(align == 1 && !(address & 0xFFFFF000))
        {
            address &= 0xFFFFF000;
            address += 0x1000;
        }
        uint32_t ret = address;
        address += sz;
        return ret;
    }
    return (uint32_t)kernel_heap_alloc(sz);
}

uint32_t kmalloc_a(uint32_t sz)
{
    return kmalloc_int(sz, 1);
}

uint32_t kmalloc(uint32_t sz)
{
    return kmalloc_int(sz, 0);
}

void kfree(void* p)
{
    kernel_heap_free(p);
}

void* krealloc(int size, void* p, int diff)
{
    void* ret = (void*)kmalloc(size);
    memcpy(p, ret, size - diff);
    kfree(p);
    return ret;
}
