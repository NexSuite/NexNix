/*
    stdlib.h - contains standard C library functions
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifndef _STDLIB_H
#define _STDLIB_H

#include "stddef.h"

// Defines and typedefs
#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0
#define RAND_MAX 32767

// Structures

typedef struct _div
{
    int quot;
    int rem;
}div_t;

typedef struct _ldiv
{
    long quot;
    long rem;
}ldiv_t;

typedef struct _lldiv
{
    long long quot;
    long long rem;
}lldiv_t;

// Function definitions
void abort();
void exit(int ret);
int abs(int num);
long labs(long num);
long long llabs(long long num);
div_t div(int num, int denom);
ldiv_t ldiv(long num, long denom);
lldiv_t lldiv(long long num, long long denom);
int atoi(const char* str);
void itoa(int i, char* str, int base);
void itoa_s(int i, char* str, int base);

#endif
