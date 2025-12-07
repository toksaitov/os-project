#include "kstd.h"

size_t k_itoa(int input, char *buffer, size_t buffer_size, int radix, bool force_sign)
{
    bool switch_case = false;
    int initial_input = input;
    char digit, *tmp_str = buffer;
    size_t num_of_chars = 1;

    switch (radix) {
        case 'b':
            radix = 2;
            break;

        case 'o':
            radix = 8;
            break;

        case 'd':
            radix = 10;
            break;

        case 'X':
            switch_case = true;
            __attribute__((fallthrough));
        case 'x':
            radix = 16;
            break;
    }

    if (radix < 2 || radix > 36) return 0;

    do { ++num_of_chars; } while (input /= radix);
    input = initial_input;

    if (input < 0) { input *= -1; ++num_of_chars; }
    else if (input > 0 && force_sign) { ++num_of_chars; }

    if (buffer_size < num_of_chars) {
        num_of_chars = 0;
    } else if (buffer != NULL) {
        do {
            digit = input%radix;

            if (digit <= 9) { *tmp_str++ = digit + '0'; }
            else { *tmp_str++ = digit - 10 + 'a'; }
        } while (input /= radix);

        if (initial_input < 0) { *tmp_str++ = '-'; }
        *tmp_str = 0;

        k_strreverse(buffer);

        if (switch_case) { k_strtoupper(buffer); }
    }

    return num_of_chars;
}
