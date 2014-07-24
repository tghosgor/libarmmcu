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

#ifndef RTC_H_
#define RTC_H_

#include <cstdint>

namespace stm32f429
{

/*class RTC
{
public:
  uint32_t static constexpr BaseAddress = 0x40002800;

public:
  enum class ClockSource : uint32_t
  {
    NoClock = 0x0,
    LSE = 0x1 <<8,
    LSI = 0x2 <<8,
    HSE = 0x3 <<8
  };

public: //Methods
  explicit RTC(ClockSource const source = ClockSource::LSI);
  RTC(RTC&& other);
  ~RTC();

  //static volatile RTC* open(ClockSource const source = ClockSource::LSI);
  //static void close(volatile RTC*);
  bool const isValid() { return m_isValid; }

  uint8_t const getHourTens() const volatile { return (m_registers.m_TR & 0x300000) >>20; }
  uint8_t const getHourUnits() const volatile { return (m_registers.m_TR & 0x0F0000) >>16; }
  uint8_t const getMinTens() const volatile { return (m_registers.m_TR & 0x7000) >>12; }
  uint8_t const getMinUnits() const volatile { return (m_registers.m_TR & 0x0F00) >>8; }
  uint8_t const getSecTens() const volatile { return (m_registers.m_TR & 0x70) >>4; }
  uint8_t const getSecUnits() const volatile { return m_registers.m_TR & 0x0F; }

private: //Registers
  struct Registers
  {
    uint32_t m_TR; //Time register
  };

public:
  Registers& m_registers;

private:
  bool m_isValid;

  static bool m_initialized;
};*/

}

#endif /* RTC_H_ */
