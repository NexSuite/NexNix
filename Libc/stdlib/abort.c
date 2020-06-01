/*
    abort.c - contains the abort libc function
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdlib.h>
#include <stdio.h>
#ifdef __is_libk
#include <kernel/kernel.h>
#include <kernel/terminal.h>
#endif

void abort()
{
    #ifdef __is_libk
    printf("An error occured!");
    asm("cli; hlt;");
    #endif
}

void exit(int ret)
{
    #ifdef __is_libk
    printf("Kernel exited with return code %d.\nYou may now safely shutdown your computer.", ret);
    asm("cli; hlt;");
    #endif
}
