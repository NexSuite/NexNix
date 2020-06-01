global get_eax

get_eax:
    ret

global get_ebx

get_ebx:
    mov eax, ebx
    ret

global get_ecx

get_ecx:
    mov eax, ecx
    ret

global get_edx

get_edx:
    mov eax, edx
    ret

global get_esi

get_esi:
    mov eax, esi
    ret

global get_edi

get_edi:
    mov eax, edi
    ret

global get_ebp

get_ebp:
    mov eax, ebp
    ret

global get_esp

get_esp:
    pop ebx
    mov eax, esp
    jmp ebx

global get_eip

get_eip:
    pop eax
    jmp eax

global get_eflags

get_eflags:
    pushf
    pop eax
    ret

global get_cs

get_cs:
    mov ax, cs
    ret

global get_ds

get_ds:
    mov ax, ds
    ret

global get_es

get_es:
    mov ax, es
    ret

global get_fs

get_fs:
    mov ax, fs
    ret

global get_gs

get_gs:
    mov ax, gs
    ret

global get_ss

get_ss:
    mov ax, ss
    ret

