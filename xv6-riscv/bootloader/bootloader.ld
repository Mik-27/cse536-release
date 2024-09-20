OUTPUT_ARCH( "riscv" )

/* Task: ensure the correct starting function. */
ENTRY( _entry )

SECTIONS
{
  /* Task: ensure the correct entry address based on where -kernel in QEMU jumps. */
  . = 0x80000000;

  /* Task lay out the sections as mentioned in the handout */
  .text : {
    *(.text .text.*)
    . = ALIGN(0x1000);
    PROVIDE(ecode = .);
  }

  .data : {
    . = ALIGN(16);
    *(.data .data.*)
    PROVIDE(edata = .);
  }

  .rodata : {
    . = ALIGN(16);
    *(.rodata .rodata.*)
    PROVIDE(erodata = .);
  }

  .bss : {
    . = ALIGN(16);
    *(.bss .bss.*)
    PROVIDE(ebss = .);
  }

  end = .;
}
