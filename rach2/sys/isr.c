#include "isr.h"

/*
 * Custom interrupt handlers
 */
isr_handler_t _isr_handlers[256];

/*
 * Calls registered interrupt handlers passing 'params' pushed from the
 * ISR common handler.
 */
void _isr_router(isr_params_t params);

/*
 * Calls registered interrupt request handlers passing 'params' pushed from
 * the IRQ common handler.
 */
void _irq_router(isr_params_t params);

void init_isr(void)
{
    k_memset(&_isr_handlers, 0, sizeof(_isr_handlers));

    __asm__ __volatile__ ("sti"); /* Enable interrupt handling. */
}

void register_isr_handler(uint8_t vector, isr_handler_t handler)
{
    _isr_handlers[vector] = handler;
}

void _isr_router(isr_params_t params)
{
#ifdef DEBUG
    k_printf("Kernel message: interrupt - 0x%X\n", params.vector);
#endif

    if (_isr_handlers[params.vector]) {
        _isr_handlers[params.vector](params);
    }
}

void _irq_router(isr_params_t params)
{
#ifdef DEBUG
    k_printf("Kernel message: IRQ - 0x%X\n", params.vector);
#endif

    if (params.vector >= 40) {
        reset_slave_pic();
    }

    reset_master_pic();

    if (_isr_handlers[params.vector]) {
        _isr_handlers[params.vector](params);
    }
}
