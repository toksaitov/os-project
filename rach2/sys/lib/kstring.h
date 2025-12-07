#ifndef _KSTRING_H_
#define _KSTRING_H_

#include "kdef.h"
#include "kctypes.h"

/*
 * Computes the length of the null-terminated string.
 */
size_t k_strlen(const char *str);

/*
 * Reverses characters in the null-terminated string.
 */
void k_strreverse(char *str);

/*
 * Converts lower case letters to upper case.
 */
void k_strtoupper(char *str);

/*
 * Writes 'n' bytes of 'c' to the byte string specified by 'ptr'.
 */
void* k_memset(void *ptr, char c, size_t n);

#endif
