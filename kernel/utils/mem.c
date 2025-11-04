#include "mem.h"

extern uint8_t __heap_start;
extern uint8_t __heap_end;

typedef struct free_block {
    uint32_t size;
    struct free_block* next;
} free_block_t;

static uint8_t* heap_ptr = &__heap_start;
static free_block_t* free_list = 0;

static uint32_t align_up(uint32_t ptr, uint32_t align) {
    return (ptr + align - 1) & ~(align - 1);
}

void* kmalloc(uint32_t size, uint32_t align) {
    free_block_t** prev = &free_list;
    free_block_t* block = free_list;

    while (block) {
        uint32_t aligned = align_up((uint32_t)(block + 1), align);
        uint32_t end = aligned + size;
        if (end <= (uint32_t)block + block->size) {
            *prev = block->next;
            return (void*)aligned;
        }
        prev = &block->next;
        block = block->next;
    }

    uint32_t ptr = align_up((uint32_t)heap_ptr, align);
    if (ptr + size > (uint32_t)&__heap_end)
        return 0;

    void* ret = (void*)ptr;
    heap_ptr = (uint8_t*)(ptr + size);
    return ret;
}

void kfree(void* ptr) {
    if (!ptr) return;
    free_block_t* block = (free_block_t*)ptr - 1;
    block->next = free_list;
    free_list = block;
}

void kmemset(void* ptr, uint8_t val, uint32_t size) {
    uint8_t* p = (uint8_t*)ptr;
    for (uint32_t i = 0; i < size; i++)
        p[i] = val;
}

void kmemcpy(void* dest, const void* src, uint32_t size) {
    uint8_t* d = (uint8_t*)dest;
    const uint8_t* s = (const uint8_t*)src;
    for (uint32_t i = 0; i < size; i++)
        d[i] = s[i];
}