/*
    event.h - contains kernel event system declarations
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifndef _EVENT_H
#define _EVENT_H

#include <stdint.h>

typedef struct _event
{
    uint32_t id;
    uint32_t joined[60];
    int num_joined;
}event;

#endif