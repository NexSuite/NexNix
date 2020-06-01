; The main boot file. GRUB gives control to this file
; Part of NexNix, Licensed under the GPL v3.0
; See LICENSE.md

; Multiboot header

extern kernel_main
extern _init
extern _fini
global entry

MBALIGN  equ  1<<0
MEMINFO  equ  1<<1
VIDINFO  equ  1<<2
FLAGS    equ  MBALIGN | MEMINFO | VIDINFO
MAGIC    equ  0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

KERNEL_VIRTUAL_BASE equ 0xC0000000
KERNEL_PAGE_NUMBER equ (KERNEL_VIRTUAL_BASE >> 22)

section .multiboot.data
align 4
MultiBootHeader:
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 800
    dd 600
    dd 32

STACKSIZE equ 16*1024

align 0x1000
BootPageDirectory:
    dd 0x00000083
    times (KERNEL_PAGE_NUMBER - 1) dd 0
    dd 0x00000083
    times (1024 - KERNEL_PAGE_NUMBER - 1) dd 0

section .multiboot.text progbits alloc exec nowrite align=16

entry:
    mov ecx, BootPageDirectory
    mov cr3, ecx

    mov ecx, cr4
    or ecx, 0x00000010
    mov cr4, ecx

    mov ecx, cr0
    or ecx, 0x80000000
    mov cr0, ecx

    jmp .StartInHigherHalf

section .text
.StartInHigherHalf:
    mov esp, stack+STACKSIZE
    ;call _init
    push eax
    add ebx, KERNEL_VIRTUAL_BASE
    push ebx
    call  kernel_main
    cli
    ;call _fini
.endloop:
    hlt
    jmp .endloop

section .bss
align 32
stack:
    resb STACKSIZE
