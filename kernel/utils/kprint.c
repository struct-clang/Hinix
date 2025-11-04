#include "kprint.h"
#include "x86.h"

#define VIDEO_MEMORY 0xB8000

static volatile uint16_t* vga = (volatile uint16_t*) VIDEO_MEMORY;
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

static void update_hardware_cursor() {
    uint16_t pos = cursor_y * VGA_WIDTH + cursor_x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void kclear() {
    uint16_t blank = (DEFAULT_COLOR << 8) | ' ';
    for (int y = 0; y < VGA_HEIGHT; y++)
        for (int x = 0; x < VGA_WIDTH; x++)
            vga[y * VGA_WIDTH + x] = blank;
    cursor_x = 0;
    cursor_y = 0;
    update_hardware_cursor();
}

void kputc(char c, uint8_t color) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (c == '\r') {
        cursor_x = 0;
    } else {
        vga[cursor_y * VGA_WIDTH + cursor_x] = ((uint16_t)color << 8) | c;
        cursor_x++;
        if (cursor_x >= VGA_WIDTH) {
            cursor_x = 0;
            cursor_y++;
        }
    }
    if (cursor_y >= VGA_HEIGHT) {
        for (int y = 1; y < VGA_HEIGHT; y++)
            for (int x = 0; x < VGA_WIDTH; x++)
                vga[(y-1) * VGA_WIDTH + x] = vga[y * VGA_WIDTH + x];
        uint16_t blank = (DEFAULT_COLOR << 8) | ' ';
        for (int x = 0; x < VGA_WIDTH; x++)
            vga[(VGA_HEIGHT-1) * VGA_WIDTH + x] = blank;
        cursor_y = VGA_HEIGHT - 1;
    }
    update_hardware_cursor();
}

void kprint(const char* str) {
    while (*str) {
        kputc(*str++, DEFAULT_COLOR);
    }
}

void kset_cursor(uint8_t x, uint8_t y) {
    if (x < VGA_WIDTH) cursor_x = x;
    if (y < VGA_HEIGHT) cursor_y = y;
    update_hardware_cursor();
}

void khide_cursor() {
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

void kprint_uint(uint32_t n) {
    char buf[11];
    int i = 10;
    buf[i] = '\0';

    if (n == 0) {
        kprint("0");
        return;
    }

    while (n > 0) {
        i--;
        buf[i] = '0' + (n % 10);
        n /= 10;
    }

    kprint(&buf[i]);
}