/*
    parllel.c - contains parallel port driver
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <kernel/kernel.h>
#include <kernel/system.h>
#include <kernel/driver_core.h>
#include <sys/io.h>
#include "parallel.h"

void parallel_data_init()
{
    outb(LPT1 + 2, 0);
}

void parallel_init()
{
    set_status_handler(DRIVER_PARALLEL, STATE_RUNNING, parallel_data_init);
}

void parallel_write_char(char c)
{
    outb(LPT1, c);
}

void parallel_write_string(char* s)
{
    for(int i = 0; i < strlen(s); i++)
        parallel_write_char(s[i]);
}
