OUTPUT_FORMAT(elf32-i386)
ENTRY(kmain)

SECTIONS
{
    . = 1M;

    .text :
    {
        *(.multiboot)
        *(.text*)
    }

    .rodata :
    {
        *(.rodata*)
    }

    .data :
    {
        *(.data*)
    }

    .bss  :
    {
        *(.bss*)
        __bss_start = .;
        . = ALIGN(4K);
        __bss_end = .;
    }

    .heap :
    {
        __heap_start = .;
        . += 0x100000;
        __heap_end = .;
    }
}
