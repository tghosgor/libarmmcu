/*
 * SCB.h
 *
 *  Created on: Apr 3, 2014
 *      Author: Tolga HOŞGÖR
 */

#ifndef SCB_H_
#define SCB_H_

namespace stm32f429
{

class SCB
{
public:
  SCB() = delete;

  static volatile SCB* const instance() { return reinterpret_cast<volatile SCB*>(0xE000ED00); }

public:
//private:
  uint32_t m_CPUID;
  uint32_t m_ICSR;  //Interrupt Control and State Register
  uint32_t m_VTOR;  //Vector Table Offset Register
  uint32_t m_AIRCR; //Application Interrupt and Reset Control Register
  uint32_t m_SCR;   //System Control Register
};

} //NS stm32f429

#endif /* SCB_H_ */
