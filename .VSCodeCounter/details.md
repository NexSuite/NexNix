# Details

Date : 2020-06-06 09:18:40

Directory /home/nexware/NexNix/src

Total : 106 files,  5444 codes, 466 comments, 1050 blanks, all 6960 lines

[summary](results.md)

## Files
| filename | language | code | comment | blank | total |
| :--- | :--- | ---: | ---: | ---: | ---: |
| [.gitattributes](/.gitattributes) | Properties | 1 | 0 | 1 | 2 |
| [.github/ISSUE_TEMPLATE/bug_report.md](/.github/ISSUE_TEMPLATE/bug_report.md) | Markdown | 30 | 0 | 9 | 39 |
| [.travis.yml](/.travis.yml) | YAML | 3 | 0 | 2 | 5 |
| [LICENSE.md](/LICENSE.md) | Markdown | 553 | 0 | 122 | 675 |
| [Libc/Makefile](/Libc/Makefile) | Makefile | 38 | 0 | 14 | 52 |
| [Libc/stdio/error.c](/Libc/stdio/error.c) | C | 7 | 5 | 3 | 15 |
| [Libc/stdio/io.c](/Libc/stdio/io.c) | C | 19 | 5 | 6 | 30 |
| [Libc/stdio/printf.c](/Libc/stdio/printf.c) | C | 156 | 5 | 5 | 166 |
| [Libc/stdlib/abort.c](/Libc/stdlib/abort.c) | C | 20 | 5 | 4 | 29 |
| [Libc/stdlib/math.c](/Libc/stdlib/math.c) | C | 36 | 5 | 8 | 49 |
| [Libc/string/memory.c](/Libc/string/memory.c) | C | 32 | 5 | 7 | 44 |
| [Libc/string/string.c](/Libc/string/string.c) | C | 148 | 12 | 33 | 193 |
| [Makefile](/Makefile) | Makefile | 28 | 0 | 8 | 36 |
| [NexNix.code-workspace](/NexNix.code-workspace) | JSON with Comments | 8 | 0 | 0 | 8 |
| [README.md](/README.md) | Markdown | 4 | 0 | 1 | 5 |
| [drivers/Makefile](/drivers/Makefile) | Makefile | 17 | 0 | 5 | 22 |
| [drivers/parallel/Makefile](/drivers/parallel/Makefile) | Makefile | 29 | 0 | 12 | 41 |
| [drivers/parallel/parallel.c](/drivers/parallel/parallel.c) | C | 27 | 5 | 6 | 38 |
| [drivers/parallel/parallel.h](/drivers/parallel/parallel.h) | C++ | 6 | 5 | 5 | 16 |
| [drivers/serial/Makefile](/drivers/serial/Makefile) | Makefile | 29 | 0 | 12 | 41 |
| [drivers/serial/serial.c](/drivers/serial/serial.c) | C | 69 | 6 | 11 | 86 |
| [drivers/serial/serial.h](/drivers/serial/serial.h) | C++ | 5 | 5 | 4 | 14 |
| [drivers/terminal/Makefile](/drivers/terminal/Makefile) | Makefile | 30 | 0 | 12 | 42 |
| [drivers/terminal/terminal.c](/drivers/terminal/terminal.c) | C | 43 | 74 | 8 | 125 |
| [drivers/terminal/terminal.h](/drivers/terminal/terminal.h) | C++ | 25 | 5 | 7 | 37 |
| [drivers/terminal/vga.c](/drivers/terminal/vga.c) | C | 30 | 5 | 7 | 42 |
| [drivers/video/Makefile](/drivers/video/Makefile) | Makefile | 29 | 0 | 12 | 41 |
| [drivers/video/font.h](/drivers/video/font.h) | C++ | 130 | 5 | 1 | 136 |
| [drivers/video/video.c](/drivers/video/video.c) | C | 104 | 5 | 17 | 126 |
| [drivers/video/video.h](/drivers/video/video.h) | C++ | 13 | 5 | 5 | 23 |
| [grub/grub-i386.cfg](/grub/grub-i386.cfg) | Properties | 5 | 0 | 2 | 7 |
| [grub/grub-x86_64.cfg](/grub/grub-x86_64.cfg) | Properties | 4 | 0 | 1 | 5 |
| [hal/Makefile](/hal/Makefile) | Makefile | 37 | 0 | 16 | 53 |
| [hal/hal-i386.h](/hal/hal-i386.h) | C++ | 86 | 5 | 10 | 101 |
| [hal/hal.c](/hal/hal.c) | C | 21 | 5 | 4 | 30 |
| [hal/i86/cmos.c](/hal/i86/cmos.c) | C | 47 | 5 | 8 | 60 |
| [hal/i86/i686/cpu.c](/hal/i86/i686/cpu.c) | C | 24 | 5 | 6 | 35 |
| [hal/i86/i686/gdt.c](/hal/i86/i686/gdt.c) | C | 40 | 5 | 5 | 50 |
| [hal/i86/i686/gdt_flush.asm](/hal/i86/i686/gdt_flush.asm) | x86 and x86_64 Assembly | 13 | 0 | 2 | 15 |
| [hal/i86/i686/idt.c](/hal/i86/i686/idt.c) | C | 44 | 5 | 7 | 56 |
| [hal/i86/i686/idt_flush.asm](/hal/i86/i686/idt_flush.asm) | x86 and x86_64 Assembly | 5 | 0 | 3 | 8 |
| [hal/i86/i686/include/cpu.h](/hal/i86/i686/include/cpu.h) | C++ | 5 | 5 | 4 | 14 |
| [hal/i86/i686/include/gdt.h](/hal/i86/i686/include/gdt.h) | C++ | 19 | 5 | 7 | 31 |
| [hal/i86/i686/include/idt.h](/hal/i86/i686/include/idt.h) | C++ | 19 | 5 | 5 | 29 |
| [hal/i86/i686/include/paging.h](/hal/i86/i686/include/paging.h) | C++ | 23 | 5 | 6 | 34 |
| [hal/i86/i686/include/tss.h](/hal/i86/i686/include/tss.h) | C++ | 33 | 5 | 5 | 43 |
| [hal/i86/i686/io.c](/hal/i86/i686/io.c) | C | 29 | 5 | 7 | 41 |
| [hal/i86/i686/irq.c](/hal/i86/i686/irq.c) | C | 91 | 5 | 11 | 107 |
| [hal/i86/i686/irq_stubs.asm](/hal/i86/i686/irq_stubs.asm) | x86 and x86_64 Assembly | 48 | 0 | 4 | 52 |
| [hal/i86/i686/isr.c](/hal/i86/i686/isr.c) | C | 145 | 5 | 7 | 157 |
| [hal/i86/i686/isr_stubs.asm](/hal/i86/i686/isr_stubs.asm) | x86 and x86_64 Assembly | 105 | 0 | 7 | 112 |
| [hal/i86/i686/paging.c](/hal/i86/i686/paging.c) | C | 153 | 6 | 25 | 184 |
| [hal/i86/i686/paging_internal.asm](/hal/i86/i686/paging_internal.asm) | x86 and x86_64 Assembly | 18 | 0 | 5 | 23 |
| [hal/i86/i686/pde.c](/hal/i86/i686/pde.c) | C | 36 | 5 | 10 | 51 |
| [hal/i86/i686/pte.c](/hal/i86/i686/pte.c) | C | 28 | 5 | 8 | 41 |
| [hal/i86/i686/regs.asm](/hal/i86/i686/regs.asm) | x86 and x86_64 Assembly | 65 | 0 | 33 | 98 |
| [hal/i86/i686/tss.c](/hal/i86/i686/tss.c) | C | 25 | 5 | 6 | 36 |
| [hal/i86/i686/tss_flush.asm](/hal/i86/i686/tss_flush.asm) | x86 and x86_64 Assembly | 5 | 0 | 1 | 6 |
| [hal/i86/include/cmos.h](/hal/i86/include/cmos.h) | C++ | 19 | 5 | 6 | 30 |
| [hal/i86/memory.c](/hal/i86/memory.c) | C | 153 | 5 | 19 | 177 |
| [hal/i86/pit.c](/hal/i86/pit.c) | C | 45 | 5 | 7 | 57 |
| [hal/i86/rtc.c](/hal/i86/rtc.c) | C | 99 | 5 | 17 | 121 |
| [hello/Makefile](/hello/Makefile) | Makefile | 31 | 0 | 14 | 45 |
| [hello/hello.c](/hello/hello.c) | C | 20 | 0 | 5 | 25 |
| [include/assert.h](/include/assert.h) | C++ | 14 | 5 | 3 | 22 |
| [include/iso646.h](/include/iso646.h) | C++ | 14 | 5 | 4 | 23 |
| [include/kernel/api.h](/include/kernel/api.h) | C++ | 12 | 5 | 6 | 23 |
| [include/kernel/driver_core.h](/include/kernel/driver_core.h) | C++ | 17 | 5 | 9 | 31 |
| [include/kernel/elf.h](/include/kernel/elf.h) | C++ | 172 | 5 | 24 | 201 |
| [include/kernel/event.h](/include/kernel/event.h) | C++ | 10 | 5 | 4 | 19 |
| [include/kernel/init.h](/include/kernel/init.h) | C++ | 23 | 5 | 6 | 34 |
| [include/kernel/kernel.h](/include/kernel/kernel.h) | C++ | 36 | 5 | 7 | 48 |
| [include/kernel/multiboot.h](/include/kernel/multiboot.h) | C++ | 89 | 5 | 11 | 105 |
| [include/kernel/system.h](/include/kernel/system.h) | C++ | 106 | 5 | 20 | 131 |
| [include/kernel/tasking.h](/include/kernel/tasking.h) | C++ | 94 | 5 | 35 | 134 |
| [include/kernel/terminal.h](/include/kernel/terminal.h) | C++ | 26 | 5 | 5 | 36 |
| [include/kernel/vfs.h](/include/kernel/vfs.h) | C++ | 43 | 5 | 11 | 59 |
| [include/stdarg.h](/include/stdarg.h) | C++ | 13 | 0 | 6 | 19 |
| [include/stdbool.h](/include/stdbool.h) | C++ | 7 | 6 | 5 | 18 |
| [include/stddef.h](/include/stddef.h) | C++ | 18 | 8 | 9 | 35 |
| [include/stdint.h](/include/stdint.h) | C++ | 11 | 6 | 5 | 22 |
| [include/stdio.h](/include/stdio.h) | C++ | 8 | 5 | 6 | 19 |
| [include/stdlib.h](/include/stdlib.h) | C++ | 33 | 8 | 10 | 51 |
| [include/string.h](/include/string.h) | C++ | 16 | 7 | 6 | 29 |
| [include/sys/io.h](/include/sys/io.h) | C++ | 8 | 5 | 6 | 19 |
| [include/sys/types.h](/include/sys/types.h) | C++ | 4 | 5 | 4 | 13 |
| [include/va_list.h](/include/va_list.h) | C++ | 11 | 0 | 3 | 14 |
| [kernel/Makefile](/kernel/Makefile) | Makefile | 50 | 0 | 14 | 64 |
| [kernel/arch/i686/boot.asm](/kernel/arch/i686/boot.asm) | x86 and x86_64 Assembly | 60 | 6 | 15 | 81 |
| [kernel/arch/i686/link.ld](/kernel/arch/i686/link.ld) | LinkerScript | 27 | 0 | 6 | 33 |
| [kernel/driver/driver.c](/kernel/driver/driver.c) | C | 60 | 5 | 10 | 75 |
| [kernel/kernel/init.c](/kernel/kernel/init.c) | C | 47 | 5 | 9 | 61 |
| [kernel/kernel/kernel.c](/kernel/kernel/kernel.c) | C | 24 | 6 | 3 | 33 |
| [kernel/kernel/panic.c](/kernel/kernel/panic.c) | C | 8 | 5 | 3 | 16 |
| [kernel/kernel/ustar.c](/kernel/kernel/ustar.c) | C | 98 | 5 | 18 | 121 |
| [kernel/kernel_memmgr/heap.c](/kernel/kernel_memmgr/heap.c) | C | 154 | 5 | 14 | 173 |
| [kernel/kernel_memmgr/include/heap.h](/kernel/kernel_memmgr/include/heap.h) | C++ | 29 | 5 | 7 | 41 |
| [kernel/proc/event.c](/kernel/proc/event.c) | C | 136 | 5 | 17 | 158 |
| [kernel/proc/loader.c](/kernel/proc/loader.c) | C | 100 | 6 | 11 | 117 |
| [kernel/proc/proc_aux.c](/kernel/proc/proc_aux.c) | C | 80 | 5 | 13 | 98 |
| [kernel/proc/queue.c](/kernel/proc/queue.c) | C | 146 | 5 | 27 | 178 |
| [kernel/proc/scheduler.c](/kernel/proc/scheduler.c) | C | 233 | 5 | 13 | 251 |
| [kernel/proc/sysapi.c](/kernel/proc/sysapi.c) | C | 38 | 5 | 8 | 51 |
| [object_manager/Makefile](/object_manager/Makefile) | Makefile | 17 | 0 | 5 | 22 |
| [object_manager/vfsys/Makefile](/object_manager/vfsys/Makefile) | Makefile | 31 | 0 | 12 | 43 |
| [object_manager/vfsys/vfsys.c](/object_manager/vfsys/vfsys.c) | C | 112 | 5 | 10 | 127 |

[summary](results.md)