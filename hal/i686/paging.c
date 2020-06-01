/*
    paging.c - contains paging functions
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdint.h>
#include <string.h>
#include <kernel/kernel.h>
#include <kernel/system.h>
#include "include/paging.h"

#define PAGE_SIZE 4096

pdirectory* _cur_directory = 0;
pdirectory* kernel_directory = 0;

uint32_t pdbr = 0;

void switch_dir(pdirectory* dir)
{
    pdbr = (uint32_t)&dir->entries;
    _cur_directory = dir;
    load_pd(pdbr);
}

inline pte* ptable_lookup_entry (ptable* p, virtual_addr addr)
{
	 if (p)
		 return &p->entries[PAGE_TABLE_INDEX (addr)];
	 return 0;
}

inline pde* pdirectory_lookup_entry (pdirectory* p, virtual_addr addr)
{
	if (p)
		return &p->entries[PAGE_TABLE_INDEX (addr)];
	return 0;
}

void map_address_space(pdirectory* dest, pdirectory* src)
{
    memcpy(dest, src, sizeof(pdirectory));
}

void delete_address_space(pdirectory* dir)
{
    free_block(dir);
}

pdirectory* get_directory ()
{
    return _cur_directory;
}

pdirectory* get_kernel_directory()
{
    return kernel_directory;
}

int alloc_page (pte* e)
{
	 void* p = alloc_block ();
	  if (!p)
		  return -1;

	 pte_set_frame (e, (uint32_t)p);
	  pte_add_attrib (e, PTE_PRESENT);

	return 0;
}

void free_page (pte* e)
{
	void* p = (void*)pte_get_frame (*e);
	if (p)
		free_block (p);

	pte_del_attrib (e, PTE_PRESENT);
}

ptable* create_page_table (pdirectory* dir, uint32_t virt, uint32_t flags)
{
    pde* e = &dir->entries[PAGE_DIRECTORY_INDEX(virt)];
    ptable* table = (ptable*)alloc_block();
    if(!table)
        return 0;
    memset(table, 0, sizeof(ptable));
    *e |= flags;
    pde_set_frame(e, (physical_addr)table);
    return table;
}

void map_address(pdirectory* dir, uint32_t virt, uint32_t phys, uint32_t flags)
{
    pde* e = &dir->entries[PAGE_DIRECTORY_INDEX((uint32_t)virt)];
    ptable* table = 0;
    if((*e & PTE_PRESENT) != PTE_PRESENT)
    {
        table = create_page_table(dir, virt, flags);
    }
    else
    {
        table = pde_get_frame((uint32_t)*e);
    }
    pte* page = &table->entries[PAGE_TABLE_INDEX(virt)];
    *page |= flags;
    pte_set_frame(page, (uint32_t)phys);
    if(dir == _cur_directory)
        flush(virt);
}

void map_4mb_address(pdirectory* dir, uint32_t virt, uint32_t phys, uint32_t flags)
{
    pde* e = &dir->entries[PAGE_DIRECTORY_INDEX(virt)];
    *e |= flags;
    pde_add_attrib(e, PDE_4MB);
    pde_set_frame(e, phys);
}

void map_page (void* phys, void* virt)
{
   pdirectory* pageDirectory = get_directory ();

   pde* e = &pageDirectory->entries [PAGE_DIRECTORY_INDEX ((uint32_t) virt)];
   if ( (*e & PTE_PRESENT) != PTE_PRESENT) {

      ptable* table = (ptable*) alloc_block ();
      if (!table)
         return;

      memset (table, 0, sizeof(ptable));

      pde* entry = &pageDirectory->entries [PAGE_DIRECTORY_INDEX ((uint32_t) virt)];

      pde_add_attrib (entry, PDE_PRESENT);
      pde_add_attrib (entry, PDE_WRITEABLE);
      pde_set_frame (entry, (uint32_t)table);
   }

   ptable* table = (ptable*) &pageDirectory->entries[PAGE_DIRECTORY_INDEX ((uint32_t)virt)];

   pte* page = &table->entries [PAGE_TABLE_INDEX ((uint32_t) virt)];

   pte_set_frame (page, (uint32_t) phys);
   pte_add_attrib (page, PTE_PRESENT);
   flush((virtual_addr)virt);
}

pdirectory* create_address_space()
{
    pdirectory* dir = alloc_block();
    if(!dir)
        return 0;
    //memset(dir, 0, sizeof(pdirectory));
    return dir;
}

void map_kernel(pdirectory* dir)
{
    memcpy(dir, kernel_directory, sizeof(pdirectory));
}

void* get_physical_address (pdirectory* dir, uint32_t virt)
{
    pde* pagedir = dir->entries;
    if (pagedir [virt >> 22] == 0)
            return 0;
    return (void*) ((uint32_t*) (pagedir[virt >> 22] & ~0xfff))[virt << 10 >> 10 >> 12];
}

void vmm_init()
{
    serial_printf("[vmm] VMM initializing.\r\n");

   pdirectory* dir = (pdirectory*) alloc_block();
   if (!dir)
      return;
    memset (dir, 0, sizeof (pdirectory));
    pde* entry = &dir->entries [PAGE_DIRECTORY_INDEX (0xC0000000) ];
    pde_add_attrib (entry, PDE_PRESENT);
    pde_add_attrib (entry, PDE_WRITEABLE);
    pde_add_attrib (entry, PDE_4MB);
    pde_set_frame (entry, (uint32_t)0x0);
	  pde* entry2 = &dir->entries [PAGE_DIRECTORY_INDEX (0xC0400000) ];
    pde_add_attrib (entry2, PDE_PRESENT);
    pde_add_attrib (entry2, PDE_WRITEABLE);
    pde_add_attrib (entry2, PDE_4MB);
    pde_set_frame (entry2, (uint32_t)0x400000);

    pde* entry3 = &dir->entries [PAGE_DIRECTORY_INDEX (0xC0800000) ];
    pde_add_attrib (entry3, PDE_PRESENT);
    pde_add_attrib (entry3, PDE_WRITEABLE);
    pde_add_attrib (entry3, PDE_4MB);
    pde_set_frame (entry3, (uint32_t)0x800000);
    pde* entry4 = &dir->entries [PAGE_DIRECTORY_INDEX (0x00000000) ];
    pde_add_attrib (entry4, PDE_PRESENT);
    pde_add_attrib (entry4, PDE_WRITEABLE);
    pde_add_attrib(entry4, PDE_4MB);
    pde_set_frame (entry4, (uint32_t)0x0);
    kernel_directory = dir;
    switch_dir (dir);
    enable_paging();
    serial_printf("[vmm] VMM initialized.\r\n");
}
