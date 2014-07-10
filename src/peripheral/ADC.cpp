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

#include <peripheral/ADC.hpp>

#include <peripheral/GPIO.hpp>
#include <register/RCC.hpp>

namespace stm32f429
{

ADC::ADC(const Module& module)
  : m_registers(*reinterpret_cast<Registers*>(baseModule + static_cast<std::size_t>(module) * 0x100))
{
  GPIO::Port portA(portA);
  portA.createPin(0, GPIO::Port::AnalogPin);

  RCC::instance()->m_APB2ENR |= 0x1 <<(8 + static_cast<std::size_t>(module));

  m_registers.m_CR2 |= 0x1;
}

void ADC::setResolution(const ADC::Resolution& res) volatile
{
  m_registers.m_CR1 &= ~(0x3 <<24); //clear old resolution
  m_registers.m_CR1 |= static_cast<uint32_t>(res) <<24; //set new resolution
}

void ADC::enableContinuous() volatile
{
  m_registers.m_CR2 |= 0x1 <<1;
}

void ADC::disableContinous() volatile
{
  m_registers.m_CR2 &= ~(0x1 <<1);
}

void ADC::startConversion() volatile
{
  m_registers.m_CR2 |= 0x1 <<30;
}

bool ADC::isEndOfConversion() volatile
{
  return m_registers.m_SR & (0x1 <<1);
}

const uint16_t ADC::getResult() volatile
{
  return m_registers.m_DR;
}

} //NS stm32f429
