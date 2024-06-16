#include "multiboot.h"
#include "io.h"
#include "constants.h"
#include "gdt.h"
#include "paging.h"

#include <stdint.h>

int main(multiboot_info_t *mbi, unsigned long magic)
{

    // Enable A20 line
    enable_a20();

    // Check if A20 line is enabled
    int a = check_a20();

    init_gdt();

    paging_init();

    // Create a pointer to the beginning of the buffer array
    uint32_t *p = mbi->framebuffer_addr;

    // Paging is working correctly
    // You can replace this with any action you deem appropriate
    // Set all the values in the buffer to the specified color
    for (int i = 0; i < mbi->framebuffer_width * mbi->framebuffer_height; i++)
    {
        *p++ = COLOR_BLUE;
    }

    return 0;
}