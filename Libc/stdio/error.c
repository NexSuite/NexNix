/*
    error.c - contains error handling functions
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdio.h>

void perror(const char* str)
{
    #ifdef __is_libk
    printf(str);
    #endif
}
