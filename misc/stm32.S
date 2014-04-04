/*
 * stm32.S
 *
 *  Created on: Apr 3, 2014
 *      Author: Tolga HOŞGÖR
 */

  .syntax unified
  .cpu cortex-m4
  .fpu softvfp
  .thumb

.global Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word  _sidata
/* start address for the .data section. defined in linker script */
.word  _sdata
/* end address for the .data section. defined in linker script */
.word  _edata
/* start address for the .bss section. defined in linker script */
.word  _sbss
/* end address for the .bss section. defined in linker script */
.word  _ebss
/* stack used for SystemInit_ExtMemCtl; always internal RAM used */

  //  .section  .text.entry
  //.weak  entry
  .type  _exit, %function //BU OLMADAN RESET OLMUYOR, BOZULUYOR
  .type  Default_Handler, %function //BU OLMADAN RESET OLMUYOR, BOZULUYOR

Default_Handler:
  ldr   sp, =_estack       /* set stack pointer */

/* Copy the data segment initializers from flash to SRAM */
  movs  r1, #0
  b  LoopCopyDataInit

//BU KOPYALAMA NE İŞE YARIYOR? BU OLMADAN ÇALIŞMIYOR.
CopyDataInit:
  ldr  r3, =_sidata
  ldr  r3, [r3, r1]
  str  r3, [r0, r1]
  adds  r1, r1, #4

LoopCopyDataInit:
  ldr  r0, =_sdata
  ldr  r3, =_edata
  adds  r2, r0, r1
  cmp  r2, r3
  bcc  CopyDataInit

  ldr  r2, =_sbss
  b  LoopFillZerobss

/* Zero fill the bss segment. */
FillZerobss:
  movs  r3, #0
  str  r3, [r2], #4

LoopFillZerobss:
  ldr  r3, = _ebss
  cmp  r2, r3
  bcc  FillZerobss

Main:
/* Call the clock system intitialization function.*/
//  bl  SystemInit
/* Call static constructors */
  bl __libc_init_array
/* Call the application's entry point.*/
  bl  main
  bx  lr
