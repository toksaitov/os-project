#ifndef _IDT_H_
#define _IDT_H_

#include "../isr.h"
#include "../pic.h"

#include "../lib/kstring.h"

/*
 * The IDT descriptor structure
 */
struct idt_descriptor {
    uint16_t offset_low;
    uint16_t segment_selector;
    uint8_t  reserved;
    uint8_t  flags;
    uint16_t offset_high;
} __attribute__((packed));

/*
 * The IDT descriptor type
 */
typedef struct idt_descriptor idt_descriptor_t;

/*
 * The IDT address structure
 */
struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

/*
 * The IDT address type
 */
typedef struct idt_ptr idt_ptr_t;

/*
 * The Interrupt Descriptor Table
 */
extern idt_descriptor_t idt_descriptors[256];

/*
 * The IDT location
 */
extern idt_ptr_t idt_address;

/*
 * Initializes the Interrupt Descriptor Table.
 */
void init_idt(void);

#endif
