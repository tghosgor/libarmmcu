ENTRY(entry)

/* Highest address of the user mode stack */
_estack = 0x20030000;    /* end of RAM */
//_estack = 0x20000000;    /* end of RAM */

MEMORY
{
  ram (rwx) : ORIGIN = 0x20000000, LENGTH = 192K
  rom (rx)  : ORIGIN = 0x08000000, LENGTH = 2048K
}

SECTIONS
{
    .vectortable :
    { 
	    . = ALIGN(4);
	    KEEP(*(.vectortable)) /* Startup code */
	    . = ALIGN(4);
    } >rom
    
    .  = 0x08000000;         /* From 0x08000000 */
        
    .text : 
    {
        *(.text)      /* Program code */
        *(.rodata)    /* Read only data */
        
    	*(.eh_frame)
    	KEEP (*(.init))
    	KEEP (*(.fini))
    } >rom

    .  = 0x20000000;  /* From 0x20000000 */      
    .data : 
    {
    	_sdata = .;        /* create a global symbol at data start */
        *(.data)      	   /* Data memory */
  		*(.data*)        /* .rodata* sections (constants, strings, etc.) */
    	_edata = .;        /* define a global symbol at data end */
    } >ram AT >rom
    
  	_sidata = LOADADDR(.data);

    .bss :
    {
   		 _sbss = .;         /* define a global symbol at bss start */
        *(.bss)       /* Zero-filled run time allocate data memory */
    	_ebss = .;         /* define a global symbol at bss start */
    } >ram AT >rom
}
