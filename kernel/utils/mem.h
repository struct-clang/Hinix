#ifndef MEM_H
#define MEM_H

#include <stdint.h>

void* kmalloc(uint32_t size, uint32_t align);
void kfree(void* ptr);
void kmemset(void* ptr, uint8_t val, uint32_t size);
void kmemcpy(void* dest, const void* src, uint32_t size);

#endif