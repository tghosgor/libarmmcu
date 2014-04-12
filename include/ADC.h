/*
  Copyright (c) 2014, Tolga HOŞGÖR
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
