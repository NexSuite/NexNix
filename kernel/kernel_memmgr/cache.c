/*
    cache.c - contains kernel cache code
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <kernel/kernel.h>
#include <kernel/system.h>
#include "include/cache.h"

cache* kernel_cache;

void init_kernel_cache()
{
    kernel_cache = (cache*)kmalloc(1 * sizeof(cache));
    memset(kernel_cache, 0, sizeof(kernel_cache));
    kernel_cache->max_size = CACHE_MAX;
    kernel_cache->cacheLayout = (header*)CACHE_HEADER_BASE;
    kernel_cache->size = CACHE_INITIAL_SIZE;
    kernel_cache->base = CACHE_BASE;
    kernel_cache->magic = MAGIC;
    kernel_cache->cacheLayout[0].magic = MAGIC;
    kernel_cache->cacheLayout[0].base = CACHE_BASE;
    kernel_cache->cacheLayout[0].size = 12;
    kernel_cache->cacheLayout[0].isFree = 1;
    kernel_cache->cacheLayout[0].isLast = 1;
    kernel_cache->cacheLayout[0].isUsable = 1;
    kernel_cache->num = 0;
}

void* kcache(void* p, size_t size)
{
  if(size < 1)
  {
      return 0;
  }

  for(int i = 0; i < 512; i++)
  {
      if(kernel_cache->cacheLayout[i].isFree == 1)
      {
          if(kernel_cache->cacheLayout[i].isUsable == 0)
              continue;

          if(kernel_cache->cacheLayout[i].size == size)
          {
                kernel_cache->cacheLayout[i].isFree = 0;
                int temp = i;
                temp++;
                kernel_cache->cacheLayout[i].heap_base = (uint32_t)p;
                kernel_cache->cacheLayout[i].isSwapped = 0;
                memcpy((void*)kernel_cache->cacheLayout[i].base, p, size);
                if(kernel_cache->cacheLayout[temp].magic != MAGIC)
                {
                    kernel_cache->cacheLayout[i].isLast = 1;
                }
                kfree(p);
                return (void*) kernel_cache->cacheLayout[i].base;
           }
           else if(kernel_cache->cacheLayout[i].size > size)
           {

              kernel_cache->cacheLayout[i].isFree = 0;
              int differnce = kernel_cache->cacheLayout[i].size - size;
              kernel_cache->cacheLayout[i].size -= differnce;
              int temp = i;
              temp++;
              if(kernel_cache->cacheLayout[temp].magic == MAGIC && kernel_cache->cacheLayout[temp].isFree == 1)
                  kernel_cache->cacheLayout[temp].base = kernel_cache->cacheLayout[temp].base - differnce;
              if(kernel_cache->cacheLayout[temp].magic != MAGIC)
              {
                  kernel_cache->cacheLayout[i].isLast = 1;
              }
              memcpy((void*)kernel_cache->cacheLayout[i].base, p, size);
              kfree(p);
              return (void*) kernel_cache->cacheLayout[i].base;
           }
           else
           {
                int temp = kernel_cache->num;
                temp++;
                kernel_cache->cacheLayout[temp].magic = MAGIC;
                kernel_cache->cacheLayout[temp].base = kernel_cache->cacheLayout[kernel_cache->num].base + kernel_cache->cacheLayout[kernel_cache->num].size;
                kernel_cache->cacheLayout[temp].isFree = 0;
                kernel_cache->cacheLayout[temp].isLast = 1;
                kernel_cache->cacheLayout[temp].size = size;
                kernel_cache->cacheLayout[temp].isUsable = 1;
                kernel_cache->num = temp;
                kernel_cache->size += size;
                memcpy((void*)kernel_cache->cacheLayout[i].base, p, size);
                kfree(p);
                return (void*)kernel_cache->cacheLayout[kernel_cache->num].base;
           }
      }
  }
  return 0;
}

void* kdecache(void* p)
{
    if(p == 0)
    {
        return (void*)0;
    }
    uint32_t base = (uint32_t)p;
    for (int i = 0; i < 512; i++)
    {
        if(kernel_cache->cacheLayout[i].base == base)
        {
            kernel_cache->cacheLayout[i].isFree = 1;
            int left, right;
            left = right = i;
            left--;
            right++;
            if(kernel_cache->cacheLayout[left].isFree == 1)
            {
                kernel_cache->cacheLayout[i].isUsable = 0;
                kernel_cache->cacheLayout[left].size += kernel_cache->cacheLayout[i].size;
            }
            if(kernel_cache->cacheLayout[right].isFree == 1)
            {
                kernel_cache->cacheLayout[i].isUsable = 0;
                kernel_cache->cacheLayout[right].size += kernel_cache->cacheLayout[i].size;
            }
            void* data = kernel_heap_alloc_cache_obj(kernel_cache->cacheLayout[i].size);
            memcpy(data, p, kernel_cache->cacheLayout[i].size);
            return data;
        }
    }
    return (void*)0;
}
