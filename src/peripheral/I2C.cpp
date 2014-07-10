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

#include <peripheral/I2C.hpp>

#include <exception.hpp>
#include <OS.hpp>
#include <peripheral/GPIO.hpp>
#include <register/RCC.hpp>

namespace stm32f429
{

const I2C::Module I2C::_1(0x40005400, std::make_pair(0x40023800 + 0x40, 0x1 <<21));
const I2C::Module I2C::_2(0x40005800, std::make_pair(0x40023800 + 0x40, 0x1 <<22));
const I2C::Module I2C::_3(0x40005C00, std::make_pair(0x40023800 + 0x40, 0x1 <<23));

I2C::I2C(const Module& module)
  : m_module(module)
{
  uint32_t& rccReg = *reinterpret_cast<uint32_t* const>(module.m_enablePairs[0].first);
  const uint32_t& rccVal = module.m_enablePairs[0].second;

  if(rccReg & rccVal != 0)
  {
    m_isValid = false;
  }
  else
  {
    m_isValid = true;

    if(module == _3)
    {
      GPIO::Port portA(GPIO::Port::A);
      GPIO::Port portC(GPIO::Port::C);
      portA.createPin(8, GPIO::Port::AlternatePin).setAF(GPIO::Port::AlPin::AF::_10);
      portC.createPin(9, GPIO::Port::AlternatePin).setAF(GPIO::Port::AlPin::AF::_10);
    }
    else
    {
      throw exception::FatalError("Unimplemented I2C module selected.");
    }

    rccReg |= rccVal;
    m_registers = reinterpret_cast<Registers*>(module.m_moduleAddress);
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
    uint32_t& rccReg = *reinterpret_cast<uint32_t* const>(m_module.m_enablePairs[0].first);
    const uint32_t& rccVal = m_module.m_enablePairs[0].second;

    rccReg &= ~(rccVal);
  }
}

} //NS stm32f429
