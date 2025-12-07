#include "idt.h"

idt_descriptor_t idt_descriptors[256];
idt_ptr_t idt_address;

/*
 * Loads IDT to the IDTR register.
 */
extern void _load_idt(idt_ptr_t*); /* implemented in idt_handler.asm */

/*
 * Sets the interrupt descriptor at 'index' in the IDT with an
 * appropriate 'offset', 'segment' selector, and 'flags' values.
 */
static void _idt_set_desciptor(size_t index, uint32_t offset,
                                             uint16_t segment_selector,
                                             uint8_t  flags);

void init_idt(void)
{
    idt_address.base  = (uintptr_t) &idt_descriptors;
    idt_address.limit = sizeof(idt_descriptor_t)*256 - 1;

    k_memset(&idt_descriptors, 0, sizeof(idt_descriptors));

    _idt_set_desciptor(0,  (uintptr_t) &isr0,  0x08, 0x8E);
    _idt_set_desciptor(1,  (uintptr_t) &isr1,  0x08, 0x8E);
    _idt_set_desciptor(2,  (uintptr_t) &isr2,  0x08, 0x8E);
    _idt_set_desciptor(3,  (uintptr_t) &isr3,  0x08, 0x8E);
    _idt_set_desciptor(4,  (uintptr_t) &isr4,  0x08, 0x8E);
    _idt_set_desciptor(5,  (uintptr_t) &isr5,  0x08, 0x8E);
    _idt_set_desciptor(6,  (uintptr_t) &isr6,  0x08, 0x8E);
    _idt_set_desciptor(7,  (uintptr_t) &isr7,  0x08, 0x8E);
    _idt_set_desciptor(8,  (uintptr_t) &isr8,  0x08, 0x8E);
    _idt_set_desciptor(9,  (uintptr_t) &isr9,  0x08, 0x8E);
    _idt_set_desciptor(10, (uintptr_t) &isr10, 0x08, 0x8E);
    _idt_set_desciptor(11, (uintptr_t) &isr11, 0x08, 0x8E);
    _idt_set_desciptor(12, (uintptr_t) &isr12, 0x08, 0x8E);
    _idt_set_desciptor(13, (uintptr_t) &isr13, 0x08, 0x8E);
    _idt_set_desciptor(14, (uintptr_t) &isr14, 0x08, 0x8E);
    _idt_set_desciptor(15, (uintptr_t) &isr15, 0x08, 0x8E);
    _idt_set_desciptor(16, (uintptr_t) &isr16, 0x08, 0x8E);
    _idt_set_desciptor(17, (uintptr_t) &isr17, 0x08, 0x8E);
    _idt_set_desciptor(18, (uintptr_t) &isr18, 0x08, 0x8E);
    _idt_set_desciptor(19, (uintptr_t) &isr19, 0x08, 0x8E);
    _idt_set_desciptor(20, (uintptr_t) &isr20, 0x08, 0x8E);
    _idt_set_desciptor(21, (uintptr_t) &isr21, 0x08, 0x8E);
    _idt_set_desciptor(22, (uintptr_t) &isr22, 0x08, 0x8E);
    _idt_set_desciptor(23, (uintptr_t) &isr23, 0x08, 0x8E);
    _idt_set_desciptor(24, (uintptr_t) &isr24, 0x08, 0x8E);
    _idt_set_desciptor(25, (uintptr_t) &isr25, 0x08, 0x8E);
    _idt_set_desciptor(26, (uintptr_t) &isr26, 0x08, 0x8E);
    _idt_set_desciptor(27, (uintptr_t) &isr27, 0x08, 0x8E);
    _idt_set_desciptor(28, (uintptr_t) &isr28, 0x08, 0x8E);
    _idt_set_desciptor(29, (uintptr_t) &isr29, 0x08, 0x8E);
    _idt_set_desciptor(30, (uintptr_t) &isr30, 0x08, 0x8E);
    _idt_set_desciptor(31, (uintptr_t) &isr31, 0x08, 0x8E);

    init_pic();

    _idt_set_desciptor(32, (uintptr_t) &irq0,  0x08, 0x8E);
    _idt_set_desciptor(33, (uintptr_t) &irq1,  0x08, 0x8E);
    _idt_set_desciptor(34, (uintptr_t) &irq2,  0x08, 0x8E);
    _idt_set_desciptor(35, (uintptr_t) &irq3,  0x08, 0x8E);
    _idt_set_desciptor(36, (uintptr_t) &irq4,  0x08, 0x8E);
    _idt_set_desciptor(37, (uintptr_t) &irq5,  0x08, 0x8E);
    _idt_set_desciptor(38, (uintptr_t) &irq6,  0x08, 0x8E);
    _idt_set_desciptor(39, (uintptr_t) &irq7,  0x08, 0x8E);
    _idt_set_desciptor(40, (uintptr_t) &irq8,  0x08, 0x8E);
    _idt_set_desciptor(41, (uintptr_t) &irq9,  0x08, 0x8E);
    _idt_set_desciptor(42, (uintptr_t) &irq10, 0x08, 0x8E);
    _idt_set_desciptor(43, (uintptr_t) &irq11, 0x08, 0x8E);
    _idt_set_desciptor(44, (uintptr_t) &irq12, 0x08, 0x8E);
    _idt_set_desciptor(45, (uintptr_t) &irq13, 0x08, 0x8E);
    _idt_set_desciptor(46, (uintptr_t) &irq14, 0x08, 0x8E);
    _idt_set_desciptor(47, (uintptr_t) &irq15, 0x08, 0x8E);

    _load_idt(&idt_address);
}

static void _idt_set_desciptor(size_t index, uint32_t offset,
                                             uint16_t segment_selector,
                                             uint8_t  flags)
{
    idt_descriptors[index].offset_low  = offset & 0xFFFF;
    idt_descriptors[index].offset_high = (offset >> 16) & 0xFFFF;

    idt_descriptors[index].segment_selector = segment_selector;

    idt_descriptors[index].reserved = 0;
    idt_descriptors[index].flags = flags;
}
