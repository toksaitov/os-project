#include "kbd.h"

uint8_t EN_us[128] = {
    0,      /* 0x0: Error code */
    27,     /* 0x1: Escape */
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
    '\b',   /* 0x0E: Backspace */
    '\t',   /* 0x0F: Tab */
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
    '\n',   /* 0x1C: Enter key */
    0,      /* 0x1D: Left control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0,      /* 0x2A: Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
    0,      /* 0x36: Right shift */
    '*',
    0,      /* 0x38: Left alt */
    ' ',    /* 0x39: Space bar */
    0,      /* 0x3A: Caps Lock */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 0x3B...0x44: F1...F10 */
    0,      /* 0x45: Num Lock*/
    0,      /* 0x46: Scroll Lock */
    0,      /* 0x47: Home */
    0,      /* 0x48: Up */
    0,      /* 0x49: Page Up */
    '-',
    0,      /* 0x4B: Left */
    0,
    0,      /* 0x4D: Right */
    '+',
    0,      /* 0x4F: End */
    0,      /* 0x50: Down */
    0,      /* 0x51: Page Down */
    0,      /* 0x52: Insert */
    0,      /* 0x53: Delete */
    0,   0,   0,
    0,      /* 0x57: F11 */
    0,      /* 0x58: F12 */
    0

    /* All others are undefined... */
};

bool _shift = false;

static void _keyboard_test(isr_params_t params);

void init_keyboard(void)
{
    register_isr_handler(33, &_keyboard_test);
}

static void _keyboard_test(isr_params_t params)
{
    (void) params;

    uint8_t scancode = inb(0x60);

    switch (scancode) {
        case 0x2A:
        case 0x36:
            _shift = true;
            break;

        case 0xAA:
        case 0xB6:
            _shift = false;
            break;

        default:
            if (!(scancode & 0x80)) {
                if (_shift) {
                    k_putc(EN_us[scancode] -  ('a' - 'A'));
                } else {
                    k_putc(EN_us[scancode]);
                }
            }

            break;
    }
}
