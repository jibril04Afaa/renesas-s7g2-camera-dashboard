ENTRY(Reset_Handler)

MEMORY
{
  FLASH     (RX)  : ORIGIN = 0x00000000, LENGTH = 0x00400000
  SRAMHS    (RWX) : ORIGIN = 0x1ffe0000, LENGTH = 0x00020000
}

SECTIONS
{
  . = ORIGIN(FLASH);

  .vector_table :
  {
    KEEP(*(.vector_table))
  } > FLASH

  .text :
  {
    *(.text)
    *(.text.*)
    *(.rodata)
    *(.rodata.*)
    _end_text = .;
  } > FLASH

  .data : AT(_end_text)
  {
    _start_data = .;
    *(.data)
    *(.data.*)
    _end_data = .;
  } > SRAMHS

  .bss :
  {
    _start_bss = .;
    *(.bss)
    *(.bss.*)
    *(COMMON)
    _end_bss = .;
  } > SRAMHS

  /* Put stack top at end of SRAMHS */
  .stack (NOLOAD) :
  {
    _stack_top = ORIGIN(SRAMHS) + LENGTH(SRAMHS);
  } > SRAMHS
}
