#ifndef _KSTD_H_
#define _KSTD_H_

#include "kdef.h"
#include "kstring.h"

/*
 * Converts an integer 'input' value to a number in base 'radix' outputting the 
 * value to a string 'buffer' (which size is equal to 'buffer_size'). A leading 
 * minus sign is added to the output string if the 'force_sign option is set.
 */
size_t k_itoa(int input, char *buffer, size_t buffer_size, int  radix, bool force_sign);

#endif
