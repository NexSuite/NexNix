/*
    memory.c - contains standard C memory functions
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <string.h>
#include <stddef.h>

void* memcpy(void* restrict dest, void* restrict src, size_t count)
{
	const char* sp = (const char*)src;
	char* dp = (char*)dest;
	for (; count != 0; count--) *dp++ = *sp++;
	return dest;
}

void memset(void* dest, int val, size_t count)
{
	unsigned char* temp = (unsigned char*)dest;
	for (; count != 0; count--, temp[count] = val);
}

unsigned short* memsetw(unsigned short* dest, unsigned short val, size_t count)
{
	unsigned short* temp = (unsigned short*)dest;
	for (; count != 0; count--)
		*temp++ = val;
	return dest;
}

int memcmp(const void* dest, const void* src, size_t count)
{
	const unsigned char *s1 = (const unsigned char*)dest;
	const unsigned char *s2 = (const unsigned char*)src;

	 while (count-- > 0)
	 {
		if (*s1++ != *s2++)
		return s1[-1] < s2[-1] ? -1 : 1;
	 }
	 return 0;
}
