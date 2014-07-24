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

#include "include/driver/I2C.hpp"

#include "include/system/exception.hpp"
#include "include/system/OS.hpp"
#include "include/driver/GPIO.hpp"
#include "include/driver/RCC.hpp"

namespace stm32f429
{
/*
constexpr I2C::Module I2C::_1;
constexpr I2C::Module I2C::_2;
constexpr I2C::Module I2C::_3;

I2C::I2C(const Module& module)
  : m_module(module)
{
  uint32_t& rccReg = *reinterpret_cast<uint32_t* const>(module.m_rccAddr);

  if(rccReg & module.m_rccVal != 0)
  {
    m_isValid = false;
  }
  else
  {
    m_isValid = true;

    if(module == _3)
    {
      RCC::enablePeriph<RCC::GPIOA>()->createPin(8, GPIO::::AlternatePin).setAF(GPIO::::AlPin::AF::_10);
      RCC::enablePeriph<RCC::GPIOC>()->createPin(9, GPIO::::AlternatePin).setAF(GPIO::::AlPin::AF::_10);
    }
    else
    {
      throw exception::FatalError("Unimplemented I2C module selected.");
    }

    rccReg |= module.m_rccVal;
    m_registers = reinterpret_cast<Registers*>(module.m_moduleAddr);
  }
}

I2C::I2C(I2C &&other)
  : m_registers(other.m_registers)
  , m_isValid(other.m_isValid)
  , m_module(other.m_module)
{
  other.m_isValid = false;
}

I2C::~I2C()
{
  if(isValid())
  {
    uint32_t& rccReg = *reinterpret_cast<uint32_t* const>(m_module.m_rccAddr);

    rccReg &= ~(m_module.m_rccVal);
  }
}*/

} //NS stm32f429
