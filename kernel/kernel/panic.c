/*
    panic.c - contains kernel panic functions
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdio.h>
#include <stdlib.h>
#include <kernel/kernel.h>

void panic(const char* str)
{
    perror("Kernel FATAL ERROR! ");
    perror(str);
}
