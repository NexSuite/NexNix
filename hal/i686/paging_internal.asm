global flush

flush:
    mov eax, [esp + 4]
    invlpg [eax]
    ret

global enable_paging

enable_paging:
    cli
    mov ecx, cr0
    or ecx, 0x80000000
    mov cr0, ecx
    ret

global load_pd
extern pdbr
load_pd:
    mov eax, [pdbr]
    mov cr3, eax
    ret
