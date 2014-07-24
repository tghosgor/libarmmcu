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

#include "include/driver/ADC.hpp"

#include "include/driver/GPIO.hpp"
#include "include/driver/RCC.hpp"

namespace stm32f429
{

ADC::ADC(const Module& module)
  : m_registers(*reinterpret_cast<Registers*>(baseModule + static_cast<std::size_t>(module) * 0x100))
{
  GPIO portA(GPIO::A);
  portA.createPin(0, GPIO::AnalogPin);

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
