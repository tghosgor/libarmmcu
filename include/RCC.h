/*
 * RCC.h
 *
 *  Created on: Apr 2, 2014
 *      Author: Tolga HOŞGÖR
 */

#ifndef RCC_H_
#define RCC_H_

#include <cstdint>

class RCC
{
public:
  static RCC* const get() { return reinterpret_cast<RCC*>(0x40023800); }

public:
//private:
  uint32_t m_CR; //Clock Control
  uint32_t m_PLLCFGR;
  uint32_t m_CFGR;
  uint32_t m_CIR;
  uint32_t m_AHB1RSTR;
  uint32_t m_AHB2RSTR;
  uint32_t m_AHB3RSTR;
  uint32_t m_Reserved1;
  uint32_t m_APB1RSTR;
  uint32_t m_APB2RSTR;
  uint32_t m_Reserved2;
  uint32_t m_Reserved3;
  uint32_t m_AHB1ENR;
  uint32_t m_AHB2ENR;
  uint32_t m_Reserved4;
  uint32_t m_APB1ENR;
  uint32_t m_APB2ENR;
  uint32_t m_Reserved5;
  uint32_t m_Reserved6;
  uint32_t m_AHB1LPENR;
  uint32_t m_AHB2LPENR;
  uint32_t m_AHB3LPENR;
  uint32_t m_Reserved7;
  uint32_t m_APB1LPENR;
  uint32_t m_APB2LPENR;
  uint32_t m_Reserved8;
  uint32_t m_Reserved9;
  uint32_t m_BDCR;
  uint32_t m_CSR;
  uint32_t m_Reserved10;
  uint32_t m_Reserved11;
  uint32_t m_SSCGR;
  uint32_t m_PLLI2SCFGR;
};

#endif /* RCC_H_ */
