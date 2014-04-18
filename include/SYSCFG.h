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

#include <EXTI.h>

#include <util.h>


namespace stm32f429
{

class SYSCFG
{
public:
  static constexpr std::size_t BaseAddress{ 0x40013800 };

public:
  SYSCFG() = delete;

  static constexpr SYSCFG volatile* const instance();

  template<std::uint8_t N>
  using EXTIModule = Module<BaseAddress + 0x08 + N * 4, (N * 4) % 16, stm32f429::EXTI<N>, EXTI<N>::BaseAddress>;

  /*using EXTI0  = EXTIModule<0x08, 0 , stm32f429::EXTI<0>>;
  using EXTI1  = EXTIModule<0x08, 4 , stm32f429::EXTI<1>>;
  using EXTI2  = EXTIModule<0x08, 8 , stm32f429::EXTI<2>>;
  using EXTI3  = EXTIModule<0x08, 12, stm32f429::EXTI<3>>;
  using EXTI4  = EXTIModule<0x0C, 0 , stm32f429::EXTI<4>>;
  using EXTI5  = EXTIModule<0x0C, 4 , stm32f429::EXTI<5>>;
  using EXTI6  = EXTIModule<0x0C, 8 , stm32f429::EXTI<6>>;
  using EXTI7  = EXTIModule<0x0C, 12, stm32f429::EXTI<7>>;
  using EXTI8  = EXTIModule<0x10, 0 , stm32f429::EXTI<8>>;
  using EXTI9  = EXTIModule<0x10, 4 , stm32f429::EXTI<9>>;
  using EXTI10 = EXTIModule<0x10, 8 , stm32f429::EXTI<10>>;
  using EXTI11 = EXTIModule<0x10, 12, stm32f429::EXTI<11>>;
  using EXTI12 = EXTIModule<0x14, 0 , stm32f429::EXTI<12>>;
  using EXTI13 = EXTIModule<0x14, 4 , stm32f429::EXTI<13>>;
  using EXTI14 = EXTIModule<0x14, 8 , stm32f429::EXTI<14>>;
  using EXTI15 = EXTIModule<0x14, 12, stm32f429::EXTI<15>>;*/

  enum class EXTISource : uint32_t
  {
    PA = 0, PB, PC, PD, PE,
    PF, PG, PH, PI, PJ
  };

  template<class Module>
  class EXTI
  {
  public:
    typename Module::RegType volatile* setSource(EXTISource const source) volatile;
  };

public:
  uint32_t m_MEMRM;     //Memory Remap
  uint32_t m_PMC;       //Peripheral Mode Configuration
  uint32_t m_EXTICR[4]; //External Interrupt Configuration N
  uint32_t m_CMPCR;     //Compensation Cell Control
};

} //NS stm32f429

#include <impl/SYSCFG.impl>

#endif /* SYSCFG_H_ */
