#include "gdt.h"

gdt_descriptor_t gdt_descriptors[5];
gdt_ptr_t gdt_address;

/*
 * Loads GDT address structure to the GDTR register and set the new segment
 * selectors in the CS, DS, SS, ES, FS, and GS registers.
 */
extern void _load_gdt(gdt_ptr_t*); /* implemented in gdt_handler.asm */

/*
 * Sets the segment descriptor at 'index' in the GDT table with an
 * appropriate 'base', 'limit', 'access', and 'flags' values.
 */
static void _gdt_set_descriptor(size_t index, uint32_t base,
                                              uint32_t limit,
                                              uint8_t  access,
                                              uint8_t  flags);

void init_gdt(void)
{
    gdt_address.base  = (uintptr_t) &gdt_descriptors;
    gdt_address.limit = sizeof(gdt_descriptor_t) * 5 - 1;

    _gdt_set_descriptor(0, 0, 0, 0, 0);                /* Null descriptor */
    _gdt_set_descriptor(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); /* Kernel code */
    _gdt_set_descriptor(2, 0, 0xFFFFFFFF, 0x92, 0xCF); /* Kernel data */
    _gdt_set_descriptor(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); /* User code */
    _gdt_set_descriptor(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); /* User data */

    _load_gdt(&gdt_address);
}

static void _gdt_set_descriptor(size_t index, uint32_t base,
                                              uint32_t limit,
                                              uint8_t access,
                                              uint8_t flags)
{
    gdt_descriptors[index].base_low    = base & 0xFFFF;
    gdt_descriptors[index].base_middle = (base >> 16) & 0xFF;
    gdt_descriptors[index].base_high   = (base >> 24) & 0xFF;

    gdt_descriptors[index].limit_low = limit & 0xFFFF;
    gdt_descriptors[index].flags_and_limit_high = (limit >> 16) & 0x0F;

    gdt_descriptors[index].access = access;
    gdt_descriptors[index].flags_and_limit_high |= flags & 0xF0;
}
