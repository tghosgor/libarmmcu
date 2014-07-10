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

#include <peripheral/RTC.hpp>

#include <OS.hpp>
#include <exception.hpp>
#include <register/PWR.hpp>
#include <register/RCC.hpp>

namespace stm32f429
{

/*volatile RTC* RTC::open(const RTC::ClockSource source)
{
  return new (reinterpret_cast<RTC*>(RTC::BaseAddress)) RTC(source);
}*/

/*void RTC::close(volatile RTC* rtc)
{
  rtc->~RTC();
}*/

bool RTC::m_initialized;

RTC::RTC(PWR& pwr, RTC::ClockSource const source)
  : m_registers(*reinterpret_cast<Registers*>(BaseAddress))
  , m_pwr(pwr)
{
  if(m_initialized) //RTC is already on
  {
    m_isValid = false;
    throw exception::Error("RTC is already enabled.");
  }
  else
  {
    m_initialized = true;
    m_isValid = true;

    pwr.disableBDWriteProtection();

    //enable selected clock in case it is not enabled
    switch(source)
    {
      case ClockSource::LSI:
        RCC::instance()->m_CSR |= 0x1 <<0; //LSI ON
        while(RCC::instance()->m_CSR & (0x1 <<1) == 0) //LSI Ready
        { }
        RCC::instance()->m_BDCR |= 0x2 <<8; //RTC Clock is LSI
        break;
      case ClockSource::LSE:
        RCC::instance()->m_BDCR |= 0x1 <<0; //LSE ON
        while(RCC::instance()->m_BDCR & (0x1 <<1) == 0 ) //LSE Ready
        { }
        RCC::instance()->m_BDCR |= 0x1 <<8; //RTC Clock is LSE
        break;
      default:
        throw exception::FatalError("Unimplemented RCC source selected.");
    }

    auto currentClockSource = RCC::instance()->m_BDCR & (0x3 <<8);

    if(currentClockSource != static_cast<uint32_t>(source)) //if clock source is same, no-op
    {
      RCC::instance()->m_BDCR |= 0x1 <<16; //Backup Domain Reset
      RCC::instance()->m_BDCR &= ~(0x3 <<8);
      RCC::instance()->m_BDCR &= ~(0x1 <<16); //Disable Backup Domain Reset
    }//if

    RCC::instance()->m_BDCR = 0x1 <<15; //RTC ON

    pwr.enableBDWriteProtection();
  }
}

RTC::RTC(RTC&& other)
  : m_registers(other.m_registers)
  , m_isValid(other.m_isValid)
  , m_pwr(other.m_pwr)
{
  other.m_isValid = false;
}

RTC::~RTC()
{
  if(isValid())
  {
    m_initialized = false;

    m_pwr.enableBDWriteProtection();

    RCC::instance()->m_CSR &= ~(0x1 <<0); //LSI OFF
    RCC::instance()->m_BDCR &= ~(0x1 <<0); //LSE OFF

    RCC::instance()->m_BDCR &= ~(0x1 <<15); //RTC OFF

    m_pwr.disableBDWriteProtection();
  }
}

} //NS stm32f429
