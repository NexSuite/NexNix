/*
    pde.c - contains page directory entry interface
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdint.h>
#include <kernel/kernel.h>
#include <kernel/system.h>
#include "include/paging.h"

void pde_add_attrib (pde* e, uint32_t attrib)
{
	*e |= attrib;
}

void pde_del_attrib (pde* e, uint32_t attrib)
{
	*e &= ~attrib;
}

void pde_set_frame (pde* e, physical_addr addr)
{
	*e = (*e & ~PDE_FRAME) | addr;
}

int pd_entry_is_present (pde e)
{
	return e & PDE_PRESENT;
}

int pde_is_writable (pde e)
{
	return e & PDE_WRITEABLE;
}

uint32_t pde_get_frame (pde e)
{
	return e & PDE_FRAME;
}

int pde_is_user (pde e)
{
	return e & PDE_USER;
}

int pde_is_4mb (pde e)
{
	return e & PDE_4MB;
}
