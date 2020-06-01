/*
    pte.c - contains page table entry interface
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdint.h>
#include <kernel/kernel.h>
#include <kernel/system.h>
#include "include/paging.h"

void pte_add_attrib (pte* e, uint32_t attrib)
{
	 *e |= attrib;
}

void pte_del_attrib (pte* e, uint32_t attrib)
{
	 *e &= ~attrib;
}

void pte_set_frame (pte* e, physical_addr addr)
{
	 *e = (*e & ~PTE_FRAME) | addr;
}

int pte_is_present (pte e)
{
	 return e & PTE_PRESENT;
}

int pt_entry_is_writable (pte e)
{
	 return e & PTE_WRITEABLE;
}

uint32_t pte_get_frame (pte e)
{
	 return e & PTE_FRAME;
}
