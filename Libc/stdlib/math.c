/*
    math.c - contains definition of math realted functions
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int abs(int num)
{
    return (unsigned)num;
}

long labs(long num)
{
    return (unsigned long)num;
}

long long llabs(long long num)
{
    return (unsigned long long)num;
}

div_t div(int num, int denom)
{
    div_t res;
    res.quot = num / denom;
    res.rem = num % denom;
    return res;
}

ldiv_t ldiv(long num, long denom)
{
    ldiv_t res;
    res.quot = num / denom;
    res.rem = num % denom;
    return res;
}

lldiv_t lldiv(long long num, long long denom)
{
    lldiv_t res;
    res.quot = num / denom;
    res.rem = num % denom;
    return res;
}
