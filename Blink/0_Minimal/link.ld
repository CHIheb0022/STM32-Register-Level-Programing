/* ******************************************* Linker script ********************************************** */ 
/* Entry Point */
ENTRY(_reset);

/* Memories definition */
MEMORY
{
  RAM    (xrw)    : ORIGIN = 0x20000000,   LENGTH = 96K
  RAM2    (xrw)    : ORIGIN = 0x10000000,   LENGTH = 32K
  FLASH    (rx)    : ORIGIN = 0x8000000,   LENGTH = 1024K
}

/* Highest address of the user mode stack */
_estack = ORIGIN(RAM) + LENGTH(RAM); /* end of "RAM" Ram type memory */

/* _estack points to the top of the RAM: to be stored in the SP at reset time using the startup code*/ 
SECTIONS {
  .vectors  : { KEEP(*(.vectors)) }   > FLASH
  .text     : { *(.text*) }           > FLASH
  .rodata   : { *(.rodata*) }         > FLASH

  .data : {
    _sdata = .;   /* .data section start */
    *(.first_data)
    *(.data SORT(.data.*))
    _edata = .;  /* .data section end */
  } > RAM AT > FLASH
  _sidata = LOADADDR(.data);

  .bss : {
    _sbss = .;              /* .bss section start */
    *(.bss SORT(.bss.*) COMMON)
    _ebss = .;              /* .bss section end */
  } > RAM 

  . = ALIGN(8);
  _end = .;     /* for cmsis_gcc.h  */
}