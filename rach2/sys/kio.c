#include "kio.h"

void k_putc(char c)
{
    unsigned char *video_memory;
    uint16_t cursor_pos;

    if (c < 31 || c == 127) {
        switch(c) {
            case CHAR_BS:
                if (x) --x;
                else if (y) { --y; x = SCREEN_NUMBER_OF_COLUMNS - 1; }

                break;

            case CHAR_HT:
                x = x - x%TAB_SIZE + TAB_SIZE;
                break;

            case CHAR_LF:
                x = 0; ++y;
                break;

            case CHAR_CR:
                x = 0;
                break;

            default:
                c = CHAR_NON_PRINTABLE;
                break;
        }

        if (c != CHAR_NON_PRINTABLE) c = CHAR_NULL;
    }

    if (c) {
        video_memory = (unsigned char *) VIDEO_COLOR_TEXT_BUFFER;
        video_memory += 2*(y*SCREEN_NUMBER_OF_COLUMNS + x);

        *(video_memory++) = c; *video_memory = get_curr_color_attr();

        ++x;
    }

    if (x >= SCREEN_NUMBER_OF_COLUMNS) { x = 0; ++y; }
    if (y >= SCREEN_NUMBER_OF_ROWS) {
        k_scroll_down();
        y = SCREEN_NUMBER_OF_ROWS - 1;
    }

    cursor_pos = y*SCREEN_NUMBER_OF_COLUMNS + x;

    outb(0x3D4, 0xE);
    outb(0x3D5, cursor_pos >> 8);
    outb(0x3D4, 0xF);
    outb(0x3D5, cursor_pos);
}

void k_puts(const char *str)
{
    if (str == NULL) return;

    while (*str) { k_putc(*str++); } k_putc(CHAR_LF);
}

void k_printf(const char *format, ...)
{
    char c, buffer[128];
    char **args = (char **) &format; ++args;

    const char *str = format;

    if (format == NULL) return;

    while ((c = *(format++))) {
        if (c == '%') {
            c = *(format++);

            switch(c) {
                case 'd':
                    k_itoa(*((unsigned int *) args++), buffer,
                           _K_PRINTF_BUFFER_SIZE_, c, false);
                    str = buffer;
                    goto string;
                case 'b':
                case 'o':
                case 'x':
                case 'X':
                    k_itoa(*((int *) args++), buffer,
                           _K_PRINTF_BUFFER_SIZE_, c, false);
                    str = buffer;
                    goto string;

                case 's':
                    str = *args++;
                    if (!str) str = "(null)";

                string:
                    while (*str) k_putc(*str++);
                    break;

                case 0:
                    break;

                case '%':
                default:
                    k_putc(c);
                    break;
            }
        }
        else k_putc(c);
    }
}

void outb(uint16_t port, uint8_t val)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (port) , "a" (val));
}

void outw(uint16_t port, uint16_t val)
{
    __asm__ __volatile__ ("outw %1, %0" : : "dN" (port) , "a" (val));
}

void outd(uint16_t port, uint32_t val)
{
    __asm__ __volatile__ ("outl %1, %0" : : "dN" (port) , "a" (val));
}

uint8_t inb(uint16_t port)
{
    uint8_t result;

    __asm__ __volatile__ ("inb %1, %0" : "=a" (result) : "dN" (port));

    return result;
}

uint16_t inw(uint16_t port)
{
    uint16_t result;

    __asm__ __volatile__ ("inw %1, %0" : "=a" (result) : "dN" (port));

    return result;
}

uint32_t ind(uint16_t port)
{
    uint32_t result;

    __asm__ __volatile__ ("inl %1, %0" : "=a" (result) : "dN" (port));

    return result;
}
