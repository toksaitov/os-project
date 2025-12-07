#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "80x25.h"

#include "../lib/kint.h"

/*
 * Color numbers that can be used to set foreground and background display
 * colors.
 */
typedef enum display_color {
    black,
    blue,
    green,
    cyan,
    red,
    magenta,
    brown,
    light_grey,
    dark_grey,
    light_blue,
    light_green,
    light_cyan,
    light_red,
    light_magenta,
    light_brown,
    white
} display_color_t;

/* Cursor 'x' position */
extern unsigned int x;

/* Cursor 'y' position */
extern unsigned int y;

/*
 * Moves the screen one line up removing 
 * content of the first line.
 */
void k_scroll_down(void);

/* Clears the screen. */
void k_cls(void);

/*
 * Set the character color to use for all subsequent display operations.
 */
void set_fore_color(display_color_t color);

/*
 * Set the background color to use for all subsequent display operations.
 */
void set_back_color(display_color_t color);

/*
 * Combines color values and returns a character attribute that can be used
 * in the VGA video memory in text mode.
 */
uint8_t get_curr_color_attr(void);

#endif
