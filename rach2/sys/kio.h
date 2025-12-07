#ifndef  _KIO_H_
#define  _KIO_H_

#include "display/display.h"

#include "lib/kdef.h"
#include "lib/kstd.h"
#include "lib/kint.h"

/* Printing */

/*
 * Null character
 */
#define CHAR_NULL '\0'

/*
 * Backspace
 */
#define CHAR_BS '\b'

/*
 * Horizontal tab
 */
#define CHAR_HT '\t'

/*
 * Tab size in spaces
 */
#define TAB_SIZE 4

/*
 * Line feed
 */
#define CHAR_LF 0x0A

/*
 * Carriage return
 */
#define CHAR_CR 0x0D

/*
 * Representation of any non-printable character
 */
#define CHAR_NON_PRINTABLE '?'

/*
 * Put a single character on the screen.
 */
void k_putc(char c);

/*
 * Print a null-terminated string on the screen.
 */
void k_puts(const char *str);

/*
 * The buffer size for arguments' interpolation in
 * 'k_printf' function
 */
#define _K_PRINTF_BUFFER_SIZE_ 128

/*
 * Prints output according to a format string.
 */
void k_printf(const char *format, ...);

/* Processor I/O */

/*
 * Copies the byte value from 'val' to the I/O
 * port specified by 'port'.
 */
void outb(uint16_t port, uint8_t  val);

/*
 * Copies the word value from 'val' to the I/O
 * port specified by 'port'.
 */
void outw(uint16_t port, uint16_t val);

/*
 * Copies the double-word value from 'val' to the I/O
 * port specified by 'port'.
 */
void outd(uint16_t port, uint32_t val);

/*
 * Returns the byte value from the I/O
 * port specified by 'port'.
 */
uint8_t inb(uint16_t port);

/*
 * Returns the word value from the I/O
 * port specified by 'port'.
 */
uint16_t inw(uint16_t port);

/*
 * Returns the double-word value from the I/O
 * port specified by 'port'.
 */
uint32_t ind(uint16_t port);

#endif
