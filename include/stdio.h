/*
    stdio.h - contains standard I/O functions
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifndef _STDIO_H
#define _STDIO_H

#include "stddef.h"

#define EOF -1

int printf(char *str, ...);
int putchar(int ic);
void perror(const char *str);

#endif
