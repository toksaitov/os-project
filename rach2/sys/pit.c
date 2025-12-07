#include "pit.h"

static void _pit_test(isr_params_t params);

void init_pit(uint32_t frequency)
{
    register_isr_handler(32, &_pit_test);

    uint32_t divisor = 1193182 / frequency;

    outb(0x43, 0x36);
    outb(0x40, (uint8_t) (divisor & 0xFF));
    outb(0x40, (uint8_t) ((divisor >> 8) & 0xFF));
}

uint32_t _counter = 0;
static void _pit_test(isr_params_t params)
{
    (void) params;

    k_printf("Tick #%d\r", _counter++);
}
