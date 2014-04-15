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

class SYSCFG
{
public:
  SYSCFG() = delete;

  static constexpr SYSCFG volatile* const instance();

  template<class Module>
  static constexpr Module getReg();

  template<class Module>
  class EXTI;

  using EXTI0  = EXTI<Module<0x08, 0>>;
  using EXTI1  = EXTI<Module<0x08, 4>>;
  using EXTI2  = EXTI<Module<0x08, 8>>;
  using EXTI3  = EXTI<Module<0x08, 12>>;
  using EXTI4  = EXTI<Module<0x0C, 0>>;
  using EXTI5  = EXTI<Module<0x0C, 4>>;
  using EXTI6  = EXTI<Module<0x0C, 8>>;
  using EXTI7  = EXTI<Module<0x0C, 12>>;
  using EXTI8  = EXTI<Module<0x10, 0>>;
  using EXTI9  = EXTI<Module<0x10, 4>>;
  using EXTI10 = EXTI<Module<0x10, 8>>;
  using EXTI11 = EXTI<Module<0x10, 12>>;
  using EXTI12 = EXTI<Module<0x14, 0>>;
  using EXTI13 = EXTI<Module<0x14, 4>>;
  using EXTI14 = EXTI<Module<0x14, 8>>;
  using EXTI15 = EXTI<Module<0x14, 12>>;

  template<class Module>
  class EXTI
  {
    friend class SYSCFG;

  public:
    enum class Source : uint32_t
    {
      PA = 0, PB, PC, PD, PE,
      PF, PG, PH, PI, PJ
    };

  public:
    void setSource(EXTI::Source const source);

  private:
    EXTI();
  }; //class EXTI

public:
  uint32_t m_MEMRM;   //Memory Remap
  uint32_t m_PMC;     //Peripheral Mode Configuration
  uint32_t m_EXTICR1; //External Interrupt Configuration 1
  uint32_t m_EXTICR2; //External Interrupt Configuration 2
  uint32_t m_EXTICR3; //External Interrupt Configuration 3
  uint32_t m_EXTICR4; //External Interrupt Configuration 4
  uint32_t m_CMPCR;   //Compensation Cell Control

private:
  static constexpr std::size_t BaseAddress{ 0x40013800 };
};

} //NS stm32f429

#include <impl/SYSCFG.impl>

#endif /* SYSCFG_H_ */
