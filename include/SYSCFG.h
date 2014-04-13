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

namespace EXTI
{
  template<std::size_t offset_, uint8_t shift_>
  struct Module : public util::ModuleInfo<offset_, shift_>
  { };

  typedef Module<0x08, 0> _0;
  typedef Module<0x08, 4> _1;
  typedef Module<0x08, 8> _2;
  typedef Module<0x08, 12> _3;
  typedef Module<0x0C, 0> _4;
  typedef Module<0x0C, 4> _5;
  typedef Module<0x0C, 8> _6;
  typedef Module<0x0C, 12> _7;
  typedef Module<0x10, 0> _8;
  typedef Module<0x10, 4> _9;
  typedef Module<0x10, 8> _10;
  typedef Module<0x10, 12> _11;
  typedef Module<0x14, 0> _12;
  typedef Module<0x14, 4> _13;
  typedef Module<0x14, 8> _14;
  typedef Module<0x14, 12> _15;

  enum : uint32_t
  {
    PA = 0, PB, PC, PD, PE,
    PF, PG, PH, PI, PJ
  };
}

template<class Module>
class Register
{
public:
  template<class Module_ = Module>
  typename std::enable_if<std::is_same<Module_, EXTI::Module<Module_::offset, Module_::size>>::value>::type
  set(uint32_t value) { }
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

template<class Module>
constexpr Register<Module> getReg() { return Register<Module>{}; }

constexpr SYSCFG volatile* const instance() { return reinterpret_cast<SYSCFG volatile* const>(0xE000ED00); }

} //NS SYSCFG
} //NS stm32f429

#endif /* SYSCFG_H_ */
