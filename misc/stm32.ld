ENTRY(entry)

/* Highest address of the user mode stack */
_estack = 0x2002FFFF;    /* end of RAM */
//_estack = 0x20000000;    /* end of RAM */

MEMORY
{
  ram (rwx) : ORIGIN = 0x20000000, LENGTH = 192K
  rom (rx)  : ORIGIN = 0x08000000, LENGTH = 2048K
}

SECTIONS
{
    .  = 0x08000000;         /* From 0x08000000 */
    .text : 
    {
        *(vectors)    /* Vector table */
        *(.text)      /* Program code */
        *(.rodata)    /* Read only data */
    } >rom

    .  = 0x20000000;  /* From 0x20000000 */      
    .data : 
    {
    	_sdata = .;        /* create a global symbol at data start */
        *(.data)      /* Data memory */
    	_edata = .;        /* define a global symbol at data end */
    } >ram AT > rom
    
  	_sidata = LOADADDR(.data);

    .bss :
    {
   		 _sbss = .;         /* define a global symbol at bss start */
        *(.bss)       /* Zero-filled run time allocate data memory */
    	_ebss = .;         /* define a global symbol at bss start */
    } >ram AT > rom
}
