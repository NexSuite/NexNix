/*
    assert.h - contains definition of assert
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdio.h>
#include <stdlib.h>

#ifdef NDEBUG
#define assert(expression) ((void) 0)
#else
#define assert(expression) \
                            if(!(expression)) { \
                            perror"Assertion Failed! File ");\
                            perror(__FILE__);\
                            perror(" on line ");\
                            printf("%d\n", __LINE__); \
                            abort(); \
                            }
#endif
