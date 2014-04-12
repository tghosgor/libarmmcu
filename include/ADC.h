/*
 * ADC.h
 *
 *  Created on: Apr 4, 2014
 *      Author: Tolga HOŞGÖR
 */

#ifndef ADC_H_
#define ADC_H_

#include <cstdint>

namespace stm32f429
{

class ADC
{
public:
  enum class Module
  {
    ADC1 = 0x40012000,
    ADC2 = 0x40012100,
    ADC2 = 0x40012200
  };

  static volatile ADC* get(Module module) { return reinterpret_cast<volatile ADC*>(module); }

public:
//private:
  uint32_t m_SR;
  uint32_t m_CR1;
  uint32_t m_CR2;
  uint32_t m_SMPR1;
  uint32_t m_SMPR2;
  uint32_t m_JOFR1;
  uint32_t m_JOFR2;
  uint32_t m_JOFR3;
  uint32_t m_JOFR4;
  uint32_t m_HTR;
  uint32_t m_LTR;
  uint32_t m_SQR1;
  uint32_t m_SQR2;
  uint32_t m_SQR3;
  uint32_t m_JSQR;
  uint32_t m_JDR1;
  uint32_t m_JDR2;
  uint32_t m_JDR3;
  uint32_t m_JDR4;
  uint32_t m_DR;

};

}

#endif /* ADC_H_ */
