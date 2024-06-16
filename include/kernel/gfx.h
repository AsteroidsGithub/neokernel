#ifndef GFX_H
#define GFX_H

#include <stdint.h>
#include <stddef.h>

void gfx_draw_bitmap(int x, int y, uint8_t *bitmap, uint32_t col);
void gfx_draw_char(int x, int y, char c, uint32_t col);
void gfx_draw_string(int x, int y, char *str, uint32_t col);
void gfx_swap_buffer();
void gfx_clear_buffer(uint32_t col);

int init_gfx(multiboot_info_t *mbi);

#endif