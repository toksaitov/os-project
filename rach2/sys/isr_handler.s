.text

# Macro for ISR without error code (pushes dummy error code 0)
.macro ISR_WITHOUT_ERROR_CODE num
    .globl isr\num
    isr\num:
        cli
        pushl $0
        pushl $\num
        jmp isr_common_handler
.endm

# Macro for ISR with error code (CPU pushes error code)
.macro ISR_WITH_ERROR_CODE num
    .globl isr\num
    isr\num:
        cli
        pushl $\num
        jmp isr_common_handler
.endm

# Generate ISR stubs (exceptions 0-31)
ISR_WITHOUT_ERROR_CODE 0
ISR_WITHOUT_ERROR_CODE 1
ISR_WITHOUT_ERROR_CODE 2
ISR_WITHOUT_ERROR_CODE 3
ISR_WITHOUT_ERROR_CODE 4
ISR_WITHOUT_ERROR_CODE 5
ISR_WITHOUT_ERROR_CODE 6
ISR_WITHOUT_ERROR_CODE 7

ISR_WITH_ERROR_CODE 8

ISR_WITHOUT_ERROR_CODE 9

ISR_WITH_ERROR_CODE 10
ISR_WITH_ERROR_CODE 11
ISR_WITH_ERROR_CODE 12
ISR_WITH_ERROR_CODE 13
ISR_WITH_ERROR_CODE 14

ISR_WITHOUT_ERROR_CODE 15
ISR_WITHOUT_ERROR_CODE 16

ISR_WITHOUT_ERROR_CODE 17

ISR_WITHOUT_ERROR_CODE 18
ISR_WITHOUT_ERROR_CODE 19
ISR_WITHOUT_ERROR_CODE 20
ISR_WITHOUT_ERROR_CODE 21
ISR_WITHOUT_ERROR_CODE 22
ISR_WITHOUT_ERROR_CODE 23
ISR_WITHOUT_ERROR_CODE 24
ISR_WITHOUT_ERROR_CODE 25
ISR_WITHOUT_ERROR_CODE 26
ISR_WITHOUT_ERROR_CODE 27
ISR_WITHOUT_ERROR_CODE 28
ISR_WITHOUT_ERROR_CODE 29
ISR_WITHOUT_ERROR_CODE 30
ISR_WITHOUT_ERROR_CODE 31

# Common ISR handler
.globl isr_common_handler
isr_common_handler:
    pushal

    movw %ds, %ax
    pushl %eax

    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    call _isr_router

    popl %eax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    popal
    addl $8, %esp
    sti

    iret

# Macro for IRQ handlers
.macro IRQ num, vector
    .globl irq\num
    irq\num:
        cli
        pushl $0
        pushl $\vector
        jmp irq_common_handler
.endm

# Generate IRQ stubs (IRQ 0-15 mapped to vectors 32-47)
IRQ 0,  32
IRQ 1,  33
IRQ 2,  34
IRQ 3,  35
IRQ 4,  36
IRQ 5,  37
IRQ 6,  38
IRQ 7,  39
IRQ 8,  40
IRQ 9,  41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

# Common IRQ handler
.globl irq_common_handler
irq_common_handler:
    pushal

    movw %ds, %ax
    pushl %eax

    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    call _irq_router

    popl %eax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    popal
    addl $8, %esp
    sti

    iret
