#include "heap.h"
#include "multiboot.h"
#include <stdint.h>
#include "gfx_font.h"
#include "memory.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define CTP(a, b) ((a > b) ? a / 2 - b / 2 : b / 2 - a / 2)

#define CLAMP(val, min, max) ((val < min) ? min : ((val > max) ? max : val))

uint32_t *framebuffer_address = NULL;
uint32_t *gfx_buffer;

uint16_t screen_width, screen_height, screen_pitch;
uint8_t screen_bpp;

void gfx_draw_bitmap(int x, int y, uint8_t *bitmap, uint32_t col)
{
    uint32_t *where = &gfx_buffer[x + y * screen_width];

    // Determine the smaller of the font and framebuffer dimensions
    int x_limit = MIN(fontWidth, screen_width - x);
    int y_limit = MIN(fontHeight, screen_height - y);

    for (int i = 0; i < y_limit; ++i)
    {
        for (int j = 0; j < x_limit; ++j)
        {
            *where++ = bitmap[i] & mask_table[j] ? col : *where;
        }
        where += screen_width - x_limit;
    }
}

int cursor_x, cursor_y;

void gfxDrawString(int x, int y, char *str, uint32_t col)
{
    cursor_x = x;
    cursor_y = y;

    while (*str)
    {
        if (*str == '\n' || cursor_x + fontWidth >= screen_width)
        {
            cursor_x = x;
            cursor_y += fontHeight;

            // If the cursor is at the bottom of the screen, scroll up
            // by the height of a character
            if (cursor_y + fontHeight >= screen_height)
                cursor_y = y;
        }
        else
        {
            gfx_draw_bitmap(cursor_x, cursor_y, term_font[*str], col);
            cursor_x += fontWidth;
        }
        str++;
    }
}

void gfx_swap_buffer()
{
    memcpy(framebuffer_address, gfx_buffer, screen_height * screen_pitch);
}

void gfx_clear_buffer(uint32_t color)
{
    memset(gfx_buffer, color, screen_height * screen_pitch);
}

int init_gfx(multiboot_info_t *mbi)
{
    if (mbi->framebuffer_bpp != 32)
        return -1;

    screen_width = mbi->framebuffer_width;
    screen_height = mbi->framebuffer_height;
    screen_pitch = mbi->framebuffer_pitch;
    screen_bpp = mbi->framebuffer_bpp;

    framebuffer_address = (uint32_t *)mbi->framebuffer_addr;

    gfx_buffer = (uint32_t)kmalloc(screen_height * screen_pitch);

    return 0;
}