/*
 * SCB.h
 *
 *  Created on: Apr 3, 2014
 *      Author: Tolga HOŞGÖR
 */

#ifndef SCB_H_
#define SCB_H_

class SCB
{
public:
  static SCB* const get() { return reinterpret_cast<SCB*>(0xE000ED00); }

public:
//private:
  uint32_t m_CPUID;
  uint32_t m_ICSR; //Interrupt Control and State Register
  uint32_t m_VTOR; //Vector Table Offset Register
};

#endif /* SCB_H_ */
