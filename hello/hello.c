#define DECL_SYSCALL1(fn,p1) int syscall_##fn(p1);

DECL_SYSCALL1(terminal_print_string, char*);
DECL_SYSCALL1(fork, int);

#define DEFN_SYSCALL1(fn, num, P1) \
int syscall_##fn(P1 p1) \
{ \
 int a; \
 asm volatile("int $48" : "=a" (a) : "0" (num), "b" ((int)p1)); \
 return a; \
}

DEFN_SYSCALL1(terminal_print_string, 0, char*);
DEFN_SYSCALL1(fork, 3, int)

void _start()
{
    syscall_terminal_print_string("Hello, User World!\n");
    for(;;)
    {
        asm("pause");
    }
}
