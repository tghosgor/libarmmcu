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

#ifndef SYSCFG_H_
#define SYSCFG_H_

#include <cstdint>
#include <type_traits>

#include <util.h>

namespace stm32f429
{
namespace SYSCFG
{

constexpr std::size_t BaseAddress{ 0x40013800 };

class EXTI
{
public:
  enum : uint32_t
  {
    _0, _1, _2, _3, _4,
    _5, _6, _7, _8, _9,
    _10, _11, _12, _13, _14,
    _15, _16, _17, _18, _19,
    _20, _21, _22
  };

  enum class Source : uint32_t
  {
    PA = 0, PB, PC, PD, PE,
    PF, PG, PH, PI, PJ
  };

  template<uint8_t idx>
  void setSource(EXTI::Source const source);
};

class SYSCFG
{
public:
  SYSCFG() = delete;

public:
//private:
  uint32_t m_MEMRM;   //Memory Remap
  uint32_t m_PMC;     //Peripheral Mode Configuration
  uint32_t m_EXTICR1; //External Interrupt Configuration 1
  uint32_t m_EXTICR2; //External Interrupt Configuration 2
  uint32_t m_EXTICR3; //External Interrupt Configuration 3
  uint32_t m_EXTICR4; //External Interrupt Configuration 4
  uint32_t m_CMPCR;   //Compensation Cell Control
};

constexpr SYSCFG volatile* const instance() { return reinterpret_cast<SYSCFG volatile* const>(BaseAddress); }

template<class Module>
constexpr Module getReg() { return Module{}; }

} //NS SYSCFG
} //NS stm32f429

#include <impl/SYSCFG.impl>

#endif /* SYSCFG_H_ */
