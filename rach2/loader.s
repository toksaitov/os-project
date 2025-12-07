.set MULTIBOOT_MAGIC,     0x1BADB002
.set MULTIBOOT_PAGEALIGN, 1
.set MULTIBOOT_MEMINFO,   1 << 1
.set MULTIBOOT_FLAGS,     MULTIBOOT_PAGEALIGN | MULTIBOOT_MEMINFO
.set MULTIBOOT_CHECKSUM,  -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)
.set KERNEL_STACK_SIZE,   0x4000

.text
.align 4

# Multiboot header
.long MULTIBOOT_MAGIC
.long MULTIBOOT_FLAGS
.long MULTIBOOT_CHECKSUM

.globl _k_entry
_k_entry:
    movl $(stack + KERNEL_STACK_SIZE), %esp

    pushl %ebx # Multiboot structure
    pushl %eax # Multiboot magic value

    call k_main

.globl k_halt
k_halt:
    hlt
    jmp k_halt

.globl k_stop
k_stop:
    cli
    hlt
    jmp k_stop

.bss
.align 4
stack:
    .skip KERNEL_STACK_SIZE
