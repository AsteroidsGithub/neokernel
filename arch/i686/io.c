#include <stdint.h>

static inline uint8_t inb(uint16_t port)
{
    uint8_t data;
    asm volatile("inb %1, %0" : "=a"(data) : "Nd"(port));
    return data;
}

static inline void outb(uint16_t port, uint8_t data)
{
    asm volatile("outb %0, %1" : : "a"(data), "Nd"(port));
}

int check_a20()
{
    volatile uint8_t *low_memory = (uint8_t *)0x00000000;
    volatile uint8_t *high_memory = (uint8_t *)0x00100000;

    uint8_t original_low = *low_memory;
    uint8_t original_high = *high_memory;
    int result;

    // Write test values
    *low_memory = 0x00;
    *high_memory = 0xFF;

    // If the values are different, A20 is enabled
    result = (*low_memory != *high_memory);

    // Restore original values
    *low_memory = original_low;
    *high_memory = original_high;

    return result;
}

int enable_a20()
{
    // Wait for keyboard controller input buffer to be empty
    while (inb(0x64) & 0x2)
        ;

    // Send write command to keyboard controller
    outb(0x64, 0xd1);

    // Wait for keyboard controller input buffer to be empty
    while (inb(0x64) & 0x2)
        ;

    // Send A20 enable command
    outb(0x60, 0xdf);

    // Wait for keyboard controller input buffer to be empty
    while (inb(0x64) & 0x2)
        ;

    return 0;
}