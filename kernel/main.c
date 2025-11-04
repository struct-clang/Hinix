#include <kernel/boot/multiboot.h>
#include <kernel/utils/kprint.h>
#include <stdint.h>

void kmain(multiboot_info_t* mb_info) {
    kclear();
    kprint("Booting kernel...");

    for (;;) {}
}
