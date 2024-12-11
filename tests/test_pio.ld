SECTIONS
{
    . = 0x00000000;

    .text : {
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }
    .pio : ALIGN(4) {
        *(.pio_section)
    } > 0x20000000
}