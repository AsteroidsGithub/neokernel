#include "multiboot.h"

#include <stdint.h>

#define gfxColor(r, g, b) ((r << 16) | (g << 8) | (b << 0))
#define gfxColorHex(hex)  gfxColor(((hex >> 16) & 0xFF), ((hex >> 8) & 0xFF), ((hex >> 0) & 0xFF))

int main(multiboot_info_t* mbi, unsigned long magic) {

    // Create a pointer to the beginning of the buffer array
    uint32_t *p = mbi->framebuffer_addr;

    // Set all the values in the buffer to the specified color
    for (int i = 0; i < mbi->framebuffer_width *mbi->framebuffer_height; i++) {
        *p++ = gfxColorHex(0x4d52e3);
    }


    return 0;
}