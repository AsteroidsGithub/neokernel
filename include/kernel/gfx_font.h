#ifndef GFX_FONT_H
#define GFX_FONT_H

#include <stdint.h>
#define fontWidth 8
#define fontHeight 12

extern uint8_t mask_table[];
extern const uint8_t gfx_cursor[fontHeight];
extern const uint8_t term_font[][fontHeight];

#endif