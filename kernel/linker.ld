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

    .rodata : { *(.rodata*) }
    .data : { *(.data*) }
    .bss  : { *(.bss*) }
}
