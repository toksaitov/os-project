ENTRY(_k_entry)

SECTIONS {
    . = 0x100000;

    .text : {
        *(.text)
    }

    .rodata ALIGN(0x1000) : {
        *(.rodata)
    }

    .data ALIGN(0x1000) : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }

    k_phys_mem_end = .;
}
