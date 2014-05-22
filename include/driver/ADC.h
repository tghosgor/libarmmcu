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

namespace
{
constexpr std::size_t baseModule = 0x40012000;
const volatile uint32_t* commonRegisters = reinterpret_cast<const volatile uint32_t*>(0x40012300);
}

class ADC
{
public:
  enum class Module : std::size_t
  {
    _1 = 0,
    _2,
    _3
  };

  enum class Resolution : uint8_t
  {
    _12Bit = 0,
    _10Bit = 0x1,
    _8Bit = 0x2,
    _6Bit = 0x3
  };

public:
  explicit ADC(const Module&);

  void setResolution(const Resolution&) volatile;

  void enableContinuous() volatile;
  void disableContinous() volatile;

  void startConversion() volatile;

  bool isEndOfConversion() volatile;

  const uint16_t getResult() volatile;

private:
  struct Registers
  {
    uint32_t m_SR;
    uint32_t m_CR1;
    uint32_t m_CR2;
    uint32_t m_SMPR[2];
    uint32_t m_JOFR[4];
    uint32_t m_HTR;
    uint32_t m_LTR;
    uint32_t m_SQR[3];
    uint32_t m_JSQR;
    uint32_t m_JDR[4];
    uint32_t m_DR;
  };

public: //Declarations
  Registers& m_registers;
};

} //NS stm32f429

#endif /* ADC_H_ */
