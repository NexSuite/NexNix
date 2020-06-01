/*
    video.h - contains video output declarations
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifndef _VIDEO_H
#define _VIDEO_H

#include <stdint.h>

typedef struct _video_info
{
    uint64_t framebufferAddr;
	uint32_t framebufferPitch;
	uint32_t framebufferWidth;
	uint32_t framebufferHeight;
	uint8_t framebufferBpp;
}video_info;

#endif
