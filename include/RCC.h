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

#ifndef RCC_H_
#define RCC_H_

#include <cstdint>

#include <util.h>

namespace stm32f429
{
namespace RCC
{

namespace GPIO
{
template<std::size_t offset_, uint8_t shift_>
struct Module : public util::ModuleInfo<offset_, shift_>
{ };

typedef Module<0x30, 0> A;
typedef Module<0x30, 1> B;
typedef Module<0x30, 2> C;
typedef Module<0x30, 3> D;
typedef Module<0x30, 4> E;
typedef Module<0x30, 5> F;
typedef Module<0x30, 6> G;
}

namespace TIM
{
template<std::size_t offset_, uint8_t shift_>
struct Module : public util::ModuleInfo<offset_, shift_>
{ };

typedef Module<0x44, 0> _1;
typedef Module<0x40, 0> _2;
typedef Module<0x40, 1> _3;
typedef Module<0x40, 2> _4;
typedef Module<0x40, 3> _5;
typedef Module<0x40, 4> _6;
typedef Module<0x40, 5> _7;
typedef Module<0x44, 1> _8;
typedef Module<0x44, 16> _9;
typedef Module<0x44, 17> _10;
typedef Module<0x44, 18> _11;
typedef Module<0x40, 6> _12;
typedef Module<0x40, 7> _13;
typedef Module<0x40, 8> _14;
}

template<class Module>
class Periph
{
public:
  void enable();
  void disable();

  void enableLPMode();
  void disableLPMode();
};

class RCC
{
public:
  RCC() = delete;

  template<class RegisterAddress>
  void enablePeriphClock();

public:
//private:
  uint32_t m_CR; //Clock Control
  uint32_t m_PLLCFGR;
  uint32_t m_CFGR;
  uint32_t m_CIR;
  uint32_t m_AHB1RSTR;
  uint32_t m_AHB2RSTR;
  uint32_t m_AHB3RSTR;
  uint32_t m_reserved1;
  uint32_t m_APB1RSTR;
  uint32_t m_APB2RSTR;
  uint32_t m_reserved2;
  uint32_t m_reserved3;
  uint32_t m_AHB1ENR;
  uint32_t m_AHB2ENR;
  uint32_t m_AHB3ENR;
  uint32_t m_reserved4;
  uint32_t m_APB1ENR;
  uint32_t m_APB2ENR;
  uint32_t m_reserved5;
  uint32_t m_reserved6;
  uint32_t m_AHB1LPENR;
  uint32_t m_AHB2LPENR;
  uint32_t m_AHB3LPENR;
  uint32_t m_reserved7;
  uint32_t m_APB1LPENR;
  uint32_t m_APB2LPENR;
  uint32_t m_reserved8;
  uint32_t m_reserved9;
  uint32_t m_BDCR;
  uint32_t m_CSR;
  uint32_t m_reserved10;
  uint32_t m_reserved11;
  uint32_t m_SSCGR;
  uint32_t m_PLLI2SCFGR;
};

static_assert(sizeof(RCC) == 0x88, "RCC size is wrong. Spec says its 88 bytes long.");

template<class Module>
constexpr Periph<Module> getPeriph()
{
  return Periph<Module>{};
}

constexpr RCC volatile* const instance()
{
  return reinterpret_cast<RCC volatile* const>(0x40023800);
}

} //NS RCC
} //NS stm32f429

#include "impl/RCC.impl"

#endif /* RCC_H_ */
