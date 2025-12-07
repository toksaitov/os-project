.text

.globl _load_idt
_load_idt:
    movl 4(%esp), %eax
    lidt (%eax)

    ret
