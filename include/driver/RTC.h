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

#ifndef RTC_H_
#define RTC_H_

#include <util.h>

#include <cstdint>

namespace stm32f429
{

class RTC
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
  RTC(ClockSource const source = ClockSource::LSI);
  RTC(RTC&& other);
  ~RTC();

  //static volatile RTC* open(ClockSource const source = ClockSource::LSI);
  //static void close(volatile RTC*);
  bool const isValid() { return m_isValid; }

  uint8_t const getHourTens() const volatile { return (m_registers->m_TR & 0x300000) >>20; }
  uint8_t const getHourUnits() const volatile { return (m_registers->m_TR & 0x0F0000) >>16; }
  uint8_t const getMinTens() const volatile { return (m_registers->m_TR & 0x7000) >>12; }
  uint8_t const getMinUnits() const volatile { return (m_registers->m_TR & 0x0F00) >>8; }
  uint8_t const getSecTens() const volatile { return (m_registers->m_TR & 0x70) >>4; }
  uint8_t const getSecUnits() const volatile { return m_registers->m_TR & 0x0F; }

private: //Registers
  struct Registers
  {
    uint32_t m_TR; //Time register
  };

public:
  Registers* m_registers;

private:
  bool m_isValid;
};

}

#endif /* RTC_H_ */
