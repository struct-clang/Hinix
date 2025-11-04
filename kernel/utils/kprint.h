#ifndef KPRINT_H
#define KPRINT_H

#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define DEFAULT_COLOR 0x07

void kclear();
void kputc(char c, uint8_t color);
void kprint(const char* str);
void kset_cursor(uint8_t x, uint8_t y);
void khide_cursor();

#endif
