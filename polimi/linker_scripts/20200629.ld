ENTRY(Reset_Handler)
MEMORY {
	flash(rx) : ORIGIN = 0x2000, LENGTH = 32K
	ram(wx)   : ORIGIN = 32*1024 + 0x2000, LENGTH = 4k
 
	/*  0x1000 = 4096 dec so 32k is 8 (* 4096) so 0x8000 */
}
_stack_top = 0xA000 + 4*1024; /*end of ram */

SECTIONS {
	. = 0; //start here
	.text {
		KEEP(*(.isr_vector))
		*(.text)
		*(.rodata)
		_init_array_start = .;

		/*
		NOT REQUESTED BY EXERCISE, support only C PROGRAMS

		if (CPP_SUPPORT)
		KEEP(*(.init_array))
		_init_array_end = .; //because I'll cycle every element to init all variables
 		*/
	} > flash

	.data {
		_data_start = .;
		*(.data);
		_data_end = .;
	} > ram AT > flash

	_bss_start = .;
	.bss {
		*(.bss)
	} > ram
	_bss_end = .;
}

	_end = .

