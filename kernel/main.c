#include "multiboot.h"
#include "io.h"
#include "constants.h"
#include "gdt.h"
#include "paging.h"
#include "gfx.h"
#include <stdint.h>

int main(multiboot_info_t *mbi, unsigned long magic)
{

    // Enable A20 line
    enable_a20();

    // Check if A20 line is enabled
    int a = check_a20();

    init_gdt();

    paging_init();

    init_gfx(mbi);

    // Clear the screen
    gfx_clear_buffer(COLOR_WHITE);

    // Draw a string
    gfxDrawString(100, 100, "Hello, World!", COLOR_BLUE);
    gfx_swap_buffer();
    return 0;
}