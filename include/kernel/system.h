/*
    system.h - contains architecture specific stuff
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifndef _KERNEL_SYSTEM_H
#define _KERNEL_SYSTEM_H

#include <stdint.h>

void outb_internal(uint16_t port, uint8_t val);
uint8_t inb_internal(uint16_t port);
void outw_internal(uint16_t port, uint16_t val);
uint16_t inw_internal(uint16_t port);
void* irq_install_handler(int num, void* handler);
void irq_remove_handler(int num);
void* irq_get_handler(int num);
void enable();
void disable();
void nmi_enable();
void nmi_disable();
int is_144_floppy();
int is_288_floppy();
int get_year();
void wait(uint64_t ticks);
int get_year();
int get_second();
int get_minute();
int get_hour();
int get_day_of_week();
int get_day();
int get_month();

#define PDE_PRESENT	1
#define PDE_WRITEABLE 2
#define PDE_USER 4
#define PDE_PWT	8
#define PDE_PCD	0x10
#define PDE_ACCESSED 0x20
#define PDE_DIRTY	0x40
#define PDE_4MB	0x80
#define PDE_CPU_GLOBAL 0x100
#define PDE_LV4_GLOBAL 0x200
#define PDE_FRAME	0x7FFFF000

#define PTE_PRESENT 1
#define PTE_WRITEABLE 2
#define PTE_USER		4
#define PTE_WRITETHOUGH	8
#define PTE_NOT_CACHEABLE	0x10
#define PTE_ACCESSED	0x20
#define PTE_DIRTY	0x40
#define PTE_PAT	0x80
#define PTE_CPU_GLOBAL 0x100
#define PTE_LV4_GLOBAL 0x200
#define PTE_FRAME	0x7FFFF000

typedef uint32_t pte;
typedef uint32_t pde;

#define PAGES_PER_TABLE 1024
#define PAGES_PER_DIR	1024
#define PAGE_SIZE 4096

#define DIR_TEMP2_BASE 0xE0001000
#define DIR_TEMP_BASE 0xE0002000
#define DIR_KERNEL_BASE 0xE0003000

typedef struct _ptable {

	pte entries[PAGES_PER_TABLE];
}ptable;

typedef struct _pdirectory {

	pde entries[PAGES_PER_DIR];
}pdirectory;

typedef uint32_t physical_addr;
typedef uint32_t virtual_addr;
void map_page (void* phys, void* virt);
void map_address(pdirectory* dir, uint32_t virt, uint32_t phys, uint32_t flags);
void switch_dir(pdirectory* dir);
pdirectory* get_directory ();
pdirectory* create_address_space();
pdirectory* get_kernel_directory();
void map_kernel(pdirectory* dir);
void map_address_space(pdirectory* dest, pdirectory* src);
void* get_physical_address (pdirectory* dir, uint32_t virt);
void map_4mb_address(pdirectory* dir, uint32_t virt, uint32_t phys, uint32_t flags);
void* alloc_page(pdirectory* dir, uint32_t virt, int is_user);

#ifdef ARCH_X86
typedef struct _regs
{
    uint32_t gs, fs, es, ds;
   	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
}regs;

void tss_set_stack(uint16_t kernel_ss, uint32_t kernel_esp);
regs* get_regs();

extern uint32_t get_eax();
extern uint32_t get_ebx();
extern uint32_t get_ecx();
extern uint32_t get_edx();
extern uint32_t get_esi();
extern uint32_t get_edi();
extern uint32_t get_esp();
extern uint32_t get_ebp();
extern uint32_t get_eip();
extern uint32_t get_eflags();
extern uint16_t get_cs();
extern uint16_t get_ds();
extern uint16_t get_es();
extern uint16_t get_fs();
extern uint16_t get_gs();
extern uint16_t get_ss();

#endif

void* alloc_block();
void free_block(void* p);
void* alloc_blocks(int num);
void free_blocks(void* p, int num);

#endif
