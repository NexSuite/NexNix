extern iptr

global idt_flush

idt_flush:
    lidt [iptr]
    ret
