/*
    sysapi.c - contains System API dispatcher
    Distributed with NexNix, Licensed under the GPL v3.0.
    See LICENSE.md
*/

#include <stdint.h>
#include <kernel/kernel.h>
#include <kernel/system.h>
#include <kernel/terminal.h>
#include <kernel/api.h>

#define MAX_SYSCALL 4

static void* syscalls [] = {
    terminal_print_string,
    terminal_write_char,
    sys_fork
};

regs* state = 0;

void* location = 0;
int ret = 0;

regs* get_regs()
{
    return state;
}

void sysapi_dispatch(regs* r)
{
    if(r->eax >= MAX_SYSCALL)
    {
        return;
    }
    state = r;
    location = syscalls[r->eax];
    asm volatile (" \
     push %1; \
     push %2; \
     push %3; \
     push %4; \
     push %5; \
     call *%6; \
     add $20, %%esp; \
   " : "=a" (ret) : "r" (r->edi), "r" (r->esi), "r" (r->edx), "r" (r->ecx), "r" (r->ebx), "r" (location));
   r->eax = ret;
   enable();
}
