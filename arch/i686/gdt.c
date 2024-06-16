#include "gdt.h"

#define GDT_ENTRIES 3

gdt_entry gdt[GDT_ENTRIES];
gdt_ptr gp;

void set_gdt_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= (granularity & 0xF0);
    gdt[num].access = access;
}

int init_gdt()
{
    gp.limit = (sizeof(gdt_entry) * GDT_ENTRIES) - 1;
    gp.base = (uint32_t)&gdt;

    set_gdt_entry(0, 0, 0, 0, 0);                // 0x00: null
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xC0); // 0x08: kernel mode text
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xC0);

    flush_gdt((uint32_t)&gp);

    return 0;
}
