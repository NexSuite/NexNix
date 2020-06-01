/*
    multiboot.h - contains multiboot structures
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/
#ifndef _MULTIBOOT_H
#define _MULTIBOOT_H

#include <stdint.h>
#include <stddef.h>

#define MULTIBOOT_BOOTLOADER_MAGIC              0x2BADB002

/*typedef struct _multiboot_info {

	uint32_t flags;
	uint32_t memLower;
	uint32_t memUpper;
	uint32_t bootDevice;
	uint32_t commandLine;
	uint32_t moduleCount;
	uint32_t moduleAddress;
	uint32_t syms[4];
	uint32_t memMapLength;
	uint32_t memMapAddress;
	uint32_t drivesLength;
	uint32_t drivesAddress;
	uint32_t configTable;
	uint32_t apmTable;
	uint32_t vbeControlInfo;
	uint32_t vbeModeInfo;
	uint32_t vbeMode;
	uint32_t vbeInterfaceSeg;
	uint32_t vbeInterfaceOff;
	uint32_t vbeInterfaceLength;
	uint64_t framebufferAddr;
	uint32_t framebufferPitch;
	uint32_t framebufferWidth;
	uint32_t framebufferHeight;
	uint8_t framebufferBpp;
	uint8_t framebufferType;
}__attribute__((packed)) multiboot_info;*/

typedef struct _multiboot_info{
	uint32_t flags;
	uint32_t memLower;
	uint32_t memUpper;
	uint32_t bootDevice;
	uint32_t cmdline;
	uint32_t moduleCount;
	uint32_t moduleAddress;
	uint32_t num;
	uint32_t size;
	uint32_t addr;
	uint32_t shndx;
	uint32_t memMapLength;
	uint32_t memMapAddress;
	uint32_t drivesLength;
	uint32_t drivesAddr;
	uint32_t configTable;
	uint32_t bootloaderName;
	uint32_t apmTable;

	uint32_t vbeControlInfo;
	uint32_t vbeModeInfo;
	uint16_t vbeMode;
	uint16_t vbeInterfaceSeg;
	uint16_t vbeInterfaceOff;
	uint16_t vbeInterfaceLen;

	uint64_t framebufferAddr;
	uint32_t framebufferPitch;
	uint32_t framebufferWidth;
	uint32_t framebufferHeight;
	uint8_t framebufferBpp;
	uint8_t framebufferType;
}__attribute__ ((packed)) multiboot_info;

typedef struct _multiboot_memory_map {
	uint32_t size;
	uint64_t base_addr;
	uint64_t length;
	uint32_t type;
} multiboot_memory_map;
typedef multiboot_memory_map mmap_entry;

typedef struct _multiboot_module
{
    uint32_t mod_start;
    uint32_t mod_end;
    char* string;
    uint32_t reserved;
}multiboot_module;

typedef struct _vbe_mode_info {
		uint16_t attributes;
		uint8_t window_a;
		uint8_t window_b;
		uint16_t granularity;
		uint16_t window_size;
		uint16_t segment_a;
		uint16_t segment_b;
		uint32_t win_func_ptr;
		uint16_t pitch;
		uint16_t width;
		uint16_t height;
		uint8_t w_char;
		uint8_t y_char;
		uint8_t planes;
		uint8_t bpp;
		uint8_t banks;
		uint8_t memory_model;
		uint8_t bank_size;
		uint8_t image_pages;
		uint8_t reserved0;
		uint8_t red_mask;
		uint8_t red_position;
		uint8_t green_mask;
		uint8_t green_position;
		uint8_t blue_mask;
		uint8_t blue_position;
		uint8_t reserved_mask;
		uint8_t reserved_position;
		uint8_t direct_color_attributes;
		uint32_t framebuffer;
		uint32_t off_screen_mem_off;
		uint16_t off_screen_mem_size;
		uint8_t reserved1[206];
} __attribute__ ((packed)) vbe_mode_info;

multiboot_info* get_boot_info();

#endif
