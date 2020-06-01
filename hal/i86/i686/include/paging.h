/*
    paging.h - contains low level paging functions
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifndef _PAGING_H
#define _PAGING_H

#define PAGE_DIRECTORY_INDEX(x) (((x) >> 22) & 0x3ff)
#define PAGE_TABLE_INDEX(x) (((x) >> 12) & 0x3ff)
#define PAGE_GET_PHYSICAL_ADDRESS(x) (*x & ~0xfff)

extern void load_pd(uint32_t pdbr);
extern void flush(uint32_t addr);
extern void enable_paging();

void pte_add_attrib (pte* e, uint32_t attrib);
void pte_del_attrib (pte* e, uint32_t attrib);
void pte_set_frame (pte* e, physical_addr addr);
int pte_is_present (pte e);
int pt_entry_is_writable (pte e);
uint32_t pte_get_frame (pte e);
int pde_is_4mb (pde e);
int pde_is_user (pde e);
uint32_t pde_get_frame (pde e);
int pde_is_writable (pde e);
int pd_entry_is_present (pde e);
void pde_set_frame (pde* e, physical_addr addr);
void pde_del_attrib (pde* e, uint32_t attrib);
void pde_add_attrib (pde* e, uint32_t attrib);

#endif
