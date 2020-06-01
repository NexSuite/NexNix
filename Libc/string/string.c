/*
    string.c - contains stdlib string functions
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

// Returns the length of a string
size_t strlen(char* str)
{
    int len = 0;
    while(str[len])
        len++;
    return len;
}

// This function copies two strings
char* strcpy(char* restrict dest, const char* src)
{
    char* temp = dest;
    while((*dest++) = *src++);
    return temp;
}

// This function compares two strings
int strcmp(char* str1, char* str2)
{
    int res = 0;
    while (!(res = *(unsigned char*)str1 - *(unsigned char*)str2) && *str2)
        ++str1, ++str2;

    if (res < 0)
        res = -1;
    if (res > 0)
        res = 1;

    return res;
}

// This function search for a character in a string
char* strrchr(char* str, int character)
{
    do {
        if (*str == character)
            return (char*)str;
    } while (*str++);

    return 0;
}

char* strchr(char *s, int c)
{
    while (*s != (char)c)
        if (!*s++)
            return 0;
    return (char*)s;
}

char* strcat(char* dest, char* src)
{
	 char* ptr = dest + strlen(dest);

	 while (*src != '\0')
		   *ptr++ = *src++;

	*ptr = '\0';

	return dest;
}


// This function converts a string to an integer
int atoi(const char* str)
{
    int result = 0;
    int sign = 1;
    int i = 0;
    if(str[0] == '-')
    {
        sign = -1;
        i++;
    }
    for(; str[i] != '\0'; ++i)
    {
        result = result * 10 + str[i] - '0';
    }

    return sign * result;
}

// This function tokenizes a string

char* sp = 0;

char* strtok(char* str, const char* delimiters)
{
    int i = 0;
    int len = strlen(delimiters);

    if(!str && !sp)
        return 0;

    if(str && !sp)
        sp = str;

    char* p_start = sp;
    for(;;)
    {
        for(i = 0; i < len; i ++)
        {
            if(*p_start == delimiters[i])
            {
                p_start ++;
                break;
            }
        }

        if(i == len) {
               sp = p_start;
               break;
        }
    }

    if(*sp == '\0')
    {
        sp = 0;
        return sp;
    }

    while(*sp != '\0')
    {
        for(i = 0; i < len; i ++)
        {
            if(*sp == delimiters[i])
            {
                *sp = '\0';
                break;
            }
        }

        sp ++;
        if (i < len)
            break;
    }

    return p_start;
}

char buf[32];
char bchars[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

// This function converts an integer into a string
void itoa(int i, char* str, int base)
{
    int pos = 0;
    int opos = 0;
    int top = 0;
    if(i == 0 || base > 16)
    {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    while (i != 0)
    {
        buf[pos] = bchars[i % base];
        pos++;
        i /= base;
    }
    top = pos--;

    for (opos = 0; opos < top; pos--, opos++) {
      str[opos] = buf[pos];
   }

   str[opos] = 0;
}

void itoa_s(int i, char* str, int base)
{
    if(base > 16)
        return;
    if(i < 0)
    {
        *str++ = '-';
        i *= -1;
    }
    itoa(i, str, base);
}
