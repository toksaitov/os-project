#include "display.h"

unsigned int x;
unsigned int y;

display_color_t _fore_color = DEFAULT_FORECOLOR;
display_color_t _back_color = DEFAULT_BACKCOLOR;

void k_cls(void)
{
    unsigned char *video_memory;
    unsigned char *video_memory_end;

    video_memory     = (unsigned char *) VIDEO_COLOR_TEXT_BUFFER;
    video_memory_end = video_memory + SCREEN_NUMBER_OF_ROWS * 
                                      SCREEN_NUMBER_OF_COLUMNS*2;

    for (; video_memory < video_memory_end; ++video_memory) {
        *video_memory = 0;
        *(video_memory + 1) = get_curr_color_attr();
    }

    x = y = 0;
}

void k_scroll_down(void)
{
    unsigned char* video_memory;
    unsigned char* video_memory_end;

    unsigned int shift;

    shift = SCREEN_NUMBER_OF_COLUMNS*2;

    video_memory = (unsigned char *) VIDEO_COLOR_TEXT_BUFFER;
    video_memory_end = video_memory + SCREEN_NUMBER_OF_ROWS * 
                                      SCREEN_NUMBER_OF_COLUMNS*2 - shift;

    for (; video_memory < video_memory_end; ++video_memory) {
        *video_memory = *(video_memory + shift);
    }

    video_memory_end += shift;

    for (; video_memory < video_memory_end; ++video_memory) {
        *video_memory = 0;
    }
}

void set_fore_color(display_color_t color)
{
    _fore_color = color;
}

void set_back_color(display_color_t color)
{
    _back_color = color;
}

uint8_t get_curr_color_attr(void)
{
    return (uint8_t) ((_fore_color & 0xF) | (_back_color << 4));
}
