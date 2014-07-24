/*
  Copyright (c) 2014, Tolga HOŞGÖR
  All rights reserved.

  This file is part of libarmmcu.

  libarmmcu is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  libarmmcu is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with libarmmcu.  If not, see <http://www.gnu.org/licenses/>
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
