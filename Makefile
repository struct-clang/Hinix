TARGET = boot/kernel
CC = gcc
LD = ld
AS = nasm

CFLAGS = -ffreestanding -O2 -Wall -Wextra -m32 -I.
LDFLAGS = -m elf_i386 -T kernel/linker.ld -nostdlib

SRCS = $(shell find kernel -name '*.c' -o -name '*.s')
OBJS = $(patsubst %.c,build/%.o,$(filter %.c,$(SRCS))) \
       $(patsubst %.s,build/%.o,$(filter %.s,$(SRCS)))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) -f elf32 $< -o $@

run: all
	mkdir -p iso/boot/grub
	cp $(TARGET) iso/boot/kernel
	cp boot/grub/grub.cfg iso/boot/grub/
	cp -r rootfs/* iso/
	grub-mkrescue -o Hinix.iso iso/

clean:
	rm -rf build $(TARGET) Hinix.iso iso
