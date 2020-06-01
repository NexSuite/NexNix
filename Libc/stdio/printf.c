/*
    printf.c - contains the printf and putchar function
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <va_list.h>
#include <stdarg.h>
#include <stdlib.h>
#ifdef __is_libk
#include <kernel/terminal.h>
#endif

int putchar(int ic)
{
    #ifdef __is_libk
    terminal_write_char((char)ic);
    #endif
    return ic;
}

int printf(char* restrict str, ...)
{
    if (!str)
        return 0;
    va_list list;
    va_start(list, str);
    size_t i;
    for(i = 0; i < strlen(str); i++)
    {
        switch(str[i])
        {
            case '%':
            {
                switch(str[i + 1])
                {
                    case 'c':
                    {
                        char c = va_arg(list, char);
                        putchar(c);
                        i++;
                        break;
                    }
                    case 's':
                    {
                        char* c = (char*)va_arg(list, char*);
                        char str[64];
                        strcpy(str, (char*)c);
                        terminal_print_string(str);
                        i++;
                        break;
                    }
                    case 'd':
                    case 'i':
                    {
                        int c = va_arg(list, int);
                        char str[64] = { 0 };
                        itoa_s(c, str, 10);
                        terminal_print_string(str);
                        i++;
                        break;
                    }
                    case 'X':
                    case 'x':
                    {
                        int c = va_arg(list, int);
                        char str[64] = { 0 };
                        itoa_s(c, str, 16);
                        terminal_print_string(str);
                        i++;
                        break;
                    }
                    default:
                    {
                        va_end(list);
                        return 1;
                    }
                }
                break;
                default:
                {
                    putchar(str[i]);
                    break;
                }
            }
        }
    }
    va_end(list);
    return i;
}

#ifdef __is_libk
int serial_printf(char* restrict str, ...)
{
    if (!str)
        return 0;
    va_list list;
    va_start(list, str);
    size_t i;
    for(i = 0; i < strlen(str); i++)
    {
        switch(str[i])
        {
            case '%':
            {
                switch(str[i + 1])
                {
                    case 'c':
                    {
                        char c = va_arg(list, char);
                        serial_write_char(c);
                        i++;
                        break;
                    }
                    case 's':
                    {
                        char* c = (char*)va_arg(list, char*);
                        char str[64];
                        strcpy(str, (char*)c);
                        serial_write_string(str);
                        i++;
                        break;
                    }
                    case 'd':
                    case 'i':
                    {
                        int c = va_arg(list, int);
                        char str[64] = { 0 };
                        itoa_s(c, str, 10);
                        serial_write_string(str);
                        i++;
                        break;
                    }
                    case 'X':
                    case 'x':
                    {
                        int c = va_arg(list, int);
                        char str[64] = { 0 };
                        itoa_s(c, str, 16);
                        serial_write_string(str);
                        i++;
                        break;
                    }
                    default:
                    {
                        va_end(list);
                        return 1;
                    }
                }
                break;
                default:
                {
                    serial_write_char(str[i]);
                    break;
                }
            }
        }
    }
    va_end(list);
    return i;
}
#endif
