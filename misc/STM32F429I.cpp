/*
 * STM32F429I.cpp
 *
 *  Created on: Apr 4, 2014
 *      Author: Tolga HOŞGÖR
 */

extern void* Default_Handler;

//__attribute__ ((section (".vectortable")))
struct VectorTable
{
  void* m_stackPointer = reinterpret_cast<void*>(0x2002FFFF);
  void* m_resetHandler = reinterpret_cast<void*>(&Default_Handler);
  void* m_NMI = reinterpret_cast<void*>(&Default_Handler);
  void* m_hardFault = reinterpret_cast<void*>(&Default_Handler);
  void* m_memoryManagementFault = reinterpret_cast<void*>(&Default_Handler);
  void* m_busFault = reinterpret_cast<void*>(&Default_Handler);
  void* m_usageFault = reinterpret_cast<void*>(&Default_Handler);
  void* m_Reserved1 = reinterpret_cast<void*>(&Default_Handler);
  void* m_Reserved2 = reinterpret_cast<void*>(&Default_Handler);
  void* m_Reserved3 = reinterpret_cast<void*>(&Default_Handler);
  void* m_Reserved4 = reinterpret_cast<void*>(&Default_Handler);
  void* m_SVCall = reinterpret_cast<void*>(&Default_Handler);
  void* m_Reserved5 = reinterpret_cast<void*>(&Default_Handler);
  void* m_Reserved6 = reinterpret_cast<void*>(&Default_Handler);
  void* m_pendSV = reinterpret_cast<void*>(&Default_Handler);
  void* m_sysTick = reinterpret_cast<void*>(&Default_Handler);
  void* m_IRQ0 = reinterpret_cast<void*>(&Default_Handler);
} vectorTable;
