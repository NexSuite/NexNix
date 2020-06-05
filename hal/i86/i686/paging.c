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

pdirectory* _cur_directory = 0;
pdirectory* kernel_directory = 0;

uint32_t pdbr = 0;

void switch_dir(pdirectory* dir)
{
    pdbr = (uint32_t)&dir->entries;
    _cur_directory = dir;
    load_pd(pdbr);
}

void map_address_space(pdirectory* dest, pdirectory* src)
{
    map_address(get_directory(), DIR_TEMP_BASE, dest, PTE_PRESENT | PTE_WRITEABLE);
    map_address(get_directory(), DIR_TEMP2_BASE, src, PTE_PRESENT | PTE_WRITEABLE);
    memcpy((void*)DIR_TEMP_BASE, (void*)DIR_TEMP2_BASE, sizeof(pdirectory));
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

ptable* create_page_table (pdirectory* dir, uint32_t virt, uint32_t flags)
{
    pde* e = &dir->entries[PAGE_DIRECTORY_INDEX(virt)];
    ptable* table = (ptable*)alloc_block();
    if(!table)
        return 0;
    *e |= flags;
    pde_set_frame(e, (physical_addr)table);
    return (ptable*)(0xFFC00000 + (PAGE_DIRECTORY_INDEX(virt) * 4096));
}

void map_address(pdirectory* dir_phys, uint32_t virt, uint32_t phys, uint32_t flags)
{
    pdirectory* temp = get_directory();
    switch_dir(dir_phys);
    pdirectory* dir = (pdirectory*)0xFFFFF000;
    pde* e = &dir->entries[PAGE_DIRECTORY_INDEX((uint32_t)virt)];
    ptable* table = 0;
    if((*e & PTE_PRESENT) != PTE_PRESENT)
    {
        table = create_page_table(dir, virt, flags);
    }
    else
    {
        table = (ptable*)(0xFFC00000 + (PAGE_DIRECTORY_INDEX(virt) * 4096));
    }
    pte* page = &table->entries[PAGE_TABLE_INDEX(virt)];
    *page |= flags;
    pte_set_frame(page, (uint32_t)phys);
    switch_dir(temp);
}

void map_4mb_address(pdirectory* dir, uint32_t virt, uint32_t phys, uint32_t flags)
{
    pde* e = &dir->entries[PAGE_DIRECTORY_INDEX(virt)];
    *e |= flags;
    pde_add_attrib(e, PDE_4MB);
    pde_set_frame(e, phys);
}

void* alloc_page(pdirectory* dir, uint32_t virt, int is_user)
{
    void* block = alloc_block();
    if(!is_user)
        map_address(dir, virt, block, PTE_PRESENT | PTE_WRITEABLE);
    else
        map_address(dir, virt, block, PTE_PRESENT | PTE_WRITEABLE | PTE_USER);
    return (void*)virt;
}

pdirectory* create_address_space()
{
    pdirectory* dir = alloc_block();
    if(!dir)
        return 0;
    return dir;
}

void map_kernel(pdirectory* dir)
{
    map_address(get_directory(), DIR_TEMP_BASE, dir, PTE_PRESENT | PTE_WRITEABLE);
    memcpy(DIR_TEMP_BASE, DIR_KERNEL_BASE, sizeof(pdirectory));
}

void* get_physical_address (pdirectory* dir, uint32_t virt)
{
    pde* pagedir = dir->entries;
    if (pagedir [virt >> 22] == 0)
            return 0;
    return (void*) ((uint32_t*) (pagedir[virt >> 22] & ~0xfff))[virt << 10 >> 10 >> 12];
}

void map_recursive(uint32_t virt, uint32_t phys, uint32_t flags)
{
    pdirectory* dir = (pdirectory*)0xFFFFF000;
    uint32_t index = PAGE_DIRECTORY_INDEX(virt);
    pde* entry = &dir->entries[index];
    if((*entry & PDE_PRESENT) == PDE_PRESENT)
    {
        ptable* table = (ptable*)(0xFFC00000 + (index * 4096));
        pte* table_entry = &table->entries[PAGE_TABLE_INDEX(virt)];
        *table_entry |= flags;
        pte_set_frame(table_entry, phys);
    }
}

void vmm_init()
{
    serial_printf("[vmm] VMM initializing.\r\n");
    pdirectory* dir = (pdirectory*) alloc_block();
    ptable* table = (ptable*)alloc_block();
    if (!dir)
        return;
    memset(dir, 0, sizeof (pdirectory));
    memset(table, 0, sizeof(ptable));
    pde* entry = &dir->entries[PAGE_DIRECTORY_INDEX (0xC0000000)];
    pde_add_attrib(entry, PDE_PRESENT);
    pde_add_attrib(entry, PDE_WRITEABLE);
    pde_add_attrib(entry, PDE_4MB);
    pde_set_frame(entry, (uint32_t)0x0);

	pde* entry2 = &dir->entries[PAGE_DIRECTORY_INDEX (0xC0400000)];
    pde_add_attrib(entry2, PDE_PRESENT);
    pde_add_attrib(entry2, PDE_WRITEABLE);
    pde_add_attrib(entry2, PDE_4MB);
    pde_set_frame(entry2, (uint32_t)0x400000);

    pde* entry3 = &dir->entries[PAGE_DIRECTORY_INDEX (0xC0800000)];
    pde_add_attrib(entry3, PDE_PRESENT);
    pde_add_attrib(entry3, PDE_WRITEABLE);
    pde_add_attrib(entry3, PDE_4MB);
    pde_set_frame(entry3, (uint32_t)0x800000);

    pde* entry4 = &dir->entries [PAGE_DIRECTORY_INDEX (0x00000000)];
    pde_add_attrib(entry4, PDE_PRESENT);
    pde_add_attrib (entry4, PDE_WRITEABLE);
    pde_add_attrib(entry4, PDE_4MB);
    pde_set_frame(entry4, (uint32_t)0x0);

    pde* entry5 = &dir->entries[1023];
    pde_add_attrib(entry5, PDE_PRESENT);
    pde_add_attrib(entry5, PDE_WRITEABLE);
    pde_set_frame(entry5, dir);

    pde* entry6 = &dir->entries[PAGE_DIRECTORY_INDEX(0x00400000)];
    pde_add_attrib(entry6, PDE_PRESENT);
    pde_add_attrib(entry6, PDE_WRITEABLE);
    pde_set_frame(entry6, table);

    kernel_directory = dir;
    switch_dir(dir);
    enable_paging();
    //pde_del_attrib(entry4, PDE_PRESENT);
    map_address(dir, DIR_KERNEL_BASE, kernel_directory, PTE_PRESENT | PTE_WRITEABLE);
    serial_printf("[vmm] VMM initialized.\r\n");
}
