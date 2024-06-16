#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

void *memset(void *buf, int val, size_t sz);
void *memcpy(void *dest, void *src, size_t sz);

#endif