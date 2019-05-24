
/* Linker script to configure memory regions. 
 * Need modifying for a specific board. 
 *   FLASH.ORIGIN: starting address of flash
 *   FLASH.LENGTH: length of flash
 *   RAM.ORIGIN: starting address of RAM bank 0
 *   RAM.LENGTH: length of RAM bank 0
 */
MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 0x10000 /* 64K */
  RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x5000 /* 20K */
}

/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and RAM.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler : Entry of reset handler
 * 
 * It defines following symbols, which code can use without definition:
 *   __rel_isrsize
 *   __initf_start
 *   __initf_end
 *   __finif_start
 *   __finif_end
 *   __etext
 *   __data_start__
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __stack
 */
ENTRY(Reset_Handler)

SECTIONS
{
	.text :
	{
		KEEP(*(.isr_vector))
        . = ALIGN(2048);

        HIDDEN(__rel_isrvector = .);
		KEEP(*(.isr_vector2))
        __rel_isrsize = . - __rel_isrvector;
        . = ALIGN(2048);

		*(.text*)

        __initf_start = .;
        *(SORT(.init_array.*))
		*(.init_array*)
        __initf_end = .;
        __finif_start = .;
		*(.fini_array*)
        *(SORT(.fini_array.*))
        __finif_end = .;

		KEEP(*(.init))
		KEEP(*(.fini))

		*(.rodata*)
	} > FLASH

	.ARM.extab : 
	{
		*(.ARM.extab* .gnu.linkonce.armextab.*)
	} > FLASH

	__exidx_start = .;
	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
	} > FLASH
	__exidx_end = .;

	/* Location counter can end up 2byte aligned with narrow Thumb code but
	   __etext is assumed by startup code to be the LMA of a section in RAM
	   which must be 4byte aligned */
	__etext = ALIGN (4);

	.data : AT (__etext)
	{
		__data_start__ = .;
		*(.data*)

		. = ALIGN(4);
		/* preinit data */
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP(*(.preinit_array))
		PROVIDE_HIDDEN (__preinit_array_end = .);

		. = ALIGN(4);
		/* init data */
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP(*(SORT(.init_array.*)))
		KEEP(*(.init_array))
		PROVIDE_HIDDEN (__init_array_end = .);


		. = ALIGN(4);
		/* finit data */
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP(*(SORT(.fini_array.*)))
		KEEP(*(.fini_array))
		PROVIDE_HIDDEN (__fini_array_end = .);

		. = ALIGN(4);
		/* All data end */
		__data_end__ = .;

	} > RAM

	.bss :
	{
		. = ALIGN(4);
		__bss_start__ = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end__ = .;
	} > RAM

	/* .stack_dummy section doesn't contains any symbols. It is only
	 * used for linker to calculate size of stack sections, and assign
	 * values to stack symbols later */
	.stack_dummy (COPY):
	{
		*(.stack*)
	} > RAM

	/* Set stack top to end of RAM, and stack limit move down by
	 * size of stack_dummy section */
	PROVIDE_HIDDEN(__StackTop = ORIGIN(RAM) + LENGTH(RAM));
	PROVIDE_HIDDEN(__StackLimit = __StackTop - SIZEOF(.stack_dummy));
	PROVIDE(__stack = __StackTop);
	
	/* Check if data + heap + stack exceeds RAM limit */
	ASSERT(__StackLimit >= LENGTH(RAM) - SIZEOF(.data) - SIZEOF(.bss), "region RAM overflowed with stack")

}
