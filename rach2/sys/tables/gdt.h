#ifndef _GDT_H_
#define _GDT_H_

#include "../lib/kdef.h"
#include "../lib/kint.h"

/*
 * The GDT descriptor structure
 */
struct gdt_descriptor {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_middle;
    uint8_t  access;
    uint8_t  flags_and_limit_high;
    uint8_t  base_high;
} __attribute__((packed));

/*
 * The GDT descriptor (type)
 */
typedef struct gdt_descriptor gdt_descriptor_t;

/*
 * The GDT address structure
 */
struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

/*
 * The GDT address (type)
 */
typedef struct gdt_ptr gdt_ptr_t;

/*
 * The Global Descriptor Table.
 */
extern gdt_descriptor_t gdt_descriptors[5];

/*
 * The GDT location and size
 */
extern gdt_ptr_t gdt_address;

/*
 * Initializes the Global Descriptor Table to flat setup.
 */
void init_gdt(void);

#endif
