#include "kprint.h"

#include <stdint.h>

static uint16_t* video_memory = (uint16_t*)0xB8000;
static int cursor = 0;

void kprint(const char* str) {
    while (*str) {
        video_memory[cursor++] = (uint16_t)(*str | 0x0F00);
        str++;
    }
}