/*
    video.c - contains VBE display output routines
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdint.h>
#include <stdio.h>
#include <sys/io.h>
#include <kernel/kernel.h>
#include <kernel/system.h>
#include <kernel/multiboot.h>
#include <kernel/driver_core.h>
#include "video.h"
#include "font.h"

multiboot_info* bootinfo = 0;
video_info vid_info;
uint32_t* framebuffer = 0;

#define VID_BUFFER 0xA0000000

void video_data_init()
{
    bootinfo = get_boot_info();
    vid_info.framebufferAddr = bootinfo->framebufferAddr;
    vid_info.framebufferBpp = bootinfo->framebufferBpp;
    vid_info.framebufferHeight = bootinfo->framebufferHeight;
    vid_info.framebufferPitch = bootinfo->framebufferPitch;
    vid_info.framebufferWidth = bootinfo->framebufferWidth;

    serial_printf("[video] Initializing screen with width %d, height %d, bpp %d, base addr %x\r\n",
     vid_info.framebufferWidth, vid_info.framebufferHeight, vid_info.framebufferBpp, vid_info.framebufferAddr);

    int size = vid_info.framebufferWidth * vid_info.framebufferHeight * (vid_info.framebufferBpp / 8);
    serial_printf("[video] Video memory size is %d bytes\r\n", size);

    for(int i = 0; i < size; i += 4096)
    {
        map_address(get_directory(), VID_BUFFER + i, vid_info.framebufferAddr + i, PTE_PRESENT | PTE_WRITEABLE);
    }
    
    framebuffer = (uint32_t*)VID_BUFFER;
    for(uint32_t i = 0; i < vid_info.framebufferWidth * vid_info.framebufferHeight; i++)
    {
        framebuffer[i] = 0x000a3cc8;
    }
}

void video_put_pixel(int x, int y, uint32_t color)
{
    uint32_t offset = y * vid_info.framebufferPitch + (x * (vid_info.framebufferBpp / 8));
    framebuffer[offset] = color;
}

void video_rect(int x, int y, uint32_t color, int width, int height)
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            framebuffer[(j + x) + (i + y) * vid_info.framebufferWidth] = color;
        }
    }
}

void video_put_char(int x, int y, uint32_t fg, char c)
{
	for (int i = 0; i < 8; i++)
	{
		int row = default_font[(int)c][i];
		for (int j = 0; j < 8; j++)
		{
			if ((row & (1 << j)) >> j)
            {
		        ((uint32_t*)framebuffer)[((y + i) * vid_info.framebufferWidth) + x + j] = fg;
            }
		}
	}
}

void video_scroll()
{
    for(int i = 0; i < 8; i++)
    {
        int i = 0;
        for(i = 0; i < vid_info.framebufferWidth * (vid_info.framebufferHeight - 1); i++)
        {
            framebuffer[i] = framebuffer[i + vid_info.framebufferWidth];
        }
        for(int i = vid_info.framebufferWidth * (vid_info.framebufferHeight - 1); i < vid_info.framebufferWidth * vid_info.framebufferHeight; i++)
           framebuffer[i] = 0x000a3cc8;
    }
}

void video_put_string(int x, int y, uint32_t fg, char* s)
{
    for(int i = 0; i < strlen(s); i++)
    {
        video_put_char(x, y, fg, s[i]);
        x += 8;
    }
}

uint32_t video_get_width()
{
    return vid_info.framebufferWidth;
}

uint32_t video_get_height()
{
    return vid_info.framebufferHeight;
}

void video_init()
{
    set_status_handler(DRIVER_VIDEO, STATE_RUNNING, video_data_init);
}
