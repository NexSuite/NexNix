/*
    string.h - contains standard C string functions
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#ifndef _STRING_H
#define _STRING_H

#include "stddef.h"

// Memory functions
int memcmp(const void* dest, const void* src, size_t size);
void* memcpy(void* restrict dest, void* restrict src, size_t size);
void memset(void* dest, int val, size_t size);
void* memmove(void* dest, const void* src, size_t size);
unsigned short* memsetw(unsigned short* dest, unsigned short val, size_t count);

// String functions
size_t strlen(char* str);
char* strcpy(char* restrict dest, const char* src);
int strcmp(char* str1, char* str2);
char* strchr(char* str, int character);
char* strrchr(char* string, int c);
char* strcat(char* dest, char* src);
char* strtok(char* str, const char* delimiters);

#endif
