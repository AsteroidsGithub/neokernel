#ifndef GDT_H
#define GDT_H

#include <stdint.h>

typedef struct
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed)) gdt_entry;

typedef struct
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdt_ptr;

void set_gdt_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);
int init_gdt();

extern void flush_gdt(uint32_t);

#endif