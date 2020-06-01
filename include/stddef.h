/*
    stddef.h - contains standard C definitions
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifndef _STDDEF_H
#define _STDDEF_H

#include "stdint.h"

// size_t definition
typedef unsigned size_t;
typedef unsigned off_t;

// ptrdiff_t definition

typedef int ptrdiff_t;

// NULL definition
#ifdef NULL
#undef NULL
#endif

#ifdef __cplusplus
extern "C"
{
    #define NULL 0
}
#else
#define NULL (void*)0
#endif

#endif
