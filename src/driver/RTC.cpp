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

#include "include/driver/RTC.hpp"

#include "include/system/OS.hpp"
#include "include/system/exception.hpp"
#include "include/driver/PWR.hpp"
#include "include/driver/RCC.hpp"

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

/*bool RTC::m_initialized;

RTC::RTC(RTC::ClockSource const source)
  : m_registers(*reinterpret_cast<Registers*>(BaseAddress))
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

    auto pwr = RCC::enablePeriph<RCC::PWR>();

    pwr->disableBDWriteProtection();

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

    pwr->enableBDWriteProtection();
  }
}

RTC::RTC(RTC&& other)
  : m_registers(other.m_registers)
  , m_isValid(other.m_isValid)
{
  other.m_isValid = false;
}

RTC::~RTC()
{
  if(isValid())
  {
    m_initialized = false;

    auto pwr = RCC::enablePeriph<RCC::PWR>();

    pwr->enableBDWriteProtection();

    RCC::instance()->m_CSR &= ~(0x1 <<0); //LSI OFF
    RCC::instance()->m_BDCR &= ~(0x1 <<0); //LSE OFF

    RCC::instance()->m_BDCR &= ~(0x1 <<15); //RTC OFF

    pwr->disableBDWriteProtection();
  }
}*/

} //NS stm32f429
