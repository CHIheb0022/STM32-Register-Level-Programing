// Startup.c


//defined in main.c
extern int main(void);

// Startup code
__attribute__((naked, noreturn)) void _reset(void) {
  // Set .bss to zero, and copy .data section to RAM region
  extern long _sbss, _ebss, _sdata, _edata, _sidata; // Defined in link.ld
  for (long *dst = &_sbss; dst < &_ebss; dst++) *dst = 0;
  for (long *dst = &_sdata, *src = &_sidata; dst < &_edata;) *dst++ = *src++;

  main();             // Call main()
  for (;;) (void) 0;  // Infinite loop in the case if main() returns
}

// Defined in link.ld
extern void _estack(void);  //Store the e_stack pointer into the SP register at reset time.  

// 16 standard and 116 STM32-specific handlers (reference manual)
__attribute__((section(".vectors"))) void (*const tab[16 + 116])(void) = {
    _estack, _reset};

// The "attribute" keyword tells the linker to put the ISR vector table into the .vector section 	




//FLASH Memory Layout//
//////.vector
		//_estack Simply a pointer placed at adress 0x8000000 points to the top of the SRAM  
		//_reset  Points to the Rest_Handler which is responsible of copying .data section into the SRAM (and zeros the .bss section)  
//////.text (code resides here)
//////.data


/*The firmware.bin file is just a concatenation of the three sections: .vectors (IRQ vector table), .text (code) and
.data (data). Those sections were built according to the linker script: .vectors lies at the very beginning of flash,
then .text follows immediately after, and .data lies far above. Addresses in .text are in the flash region, and addresses
in .data are in the RAM region. If some function has address e.g. 0x8000100, then it is located exactly at that address on flash.
But if the code accesses some variable in the .data section by the address e.g. 0x20000200, then there is nothing at that address,
because at boot, .data section in the firmware.bin resides in flash! That's why the startup code must relocate .data section from flash region to the RAM region.*/


//we have three sections of data:
//.rodata section  (read only data (const and defines))
//.data section  (contains data that is not initialized) 
//.bss section (data that is initialized to zero)