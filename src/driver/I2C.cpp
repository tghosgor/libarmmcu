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

#include <driver/I2C.h>

#include <OS.h>
#include <driver/GPIO.h>
#include <driver/RCC.h>

namespace stm32f429
{

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
      RCC::enablePeriph<RCC::GPIOA>()->createPin(8, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_10);
      RCC::enablePeriph<RCC::GPIOC>()->createPin(9, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_10);
    }
    else
    {
      OS::halt("Unimplemented I2C module selected.");
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
}

} //NS stm32f429
