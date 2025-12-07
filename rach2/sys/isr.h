#ifndef _ISR_H_
#define _ISR_H_

#include "kio.h"
#include "pic.h"

#include "lib/kint.h"
#include "lib/kstring.h"

/*
 * Parameters pushed on the stack from the ISR common procedure
 */
struct isr_params {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t vector;
    uint32_t error_code;
    uint32_t eip, cs, eflags, user_esp, user_ss;
};

/*
 * Parameters pushed on the stack from the ISR common procedure (type)
 */
typedef struct isr_params isr_params_t;

/*
 * The type of the function prototype of the interrupt handler
 */
typedef void (*isr_handler_t)(isr_params_t);

/*
 * First 32 interrupt handlers
 */
extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);

/*
 * First 15 interrupt request handlers
 */
extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);

/*
 * Initializes interrupt handling structures.
 */
void init_isr(void);

/*
 * Registers a custom interrupt 'handler' for a specific interrupt 'vector'.
 */
void register_isr_handler(uint8_t vector, isr_handler_t handler);

#endif
