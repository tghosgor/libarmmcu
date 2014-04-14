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

  typedef EXTI<Module<0x08, 0>>  EXTI0;
  typedef EXTI<Module<0x08, 4>>  EXTI1;
  typedef EXTI<Module<0x08, 8>>  EXTI2;
  typedef EXTI<Module<0x08, 12>> EXTI3;
  typedef EXTI<Module<0x0C, 0>>  EXTI4;
  typedef EXTI<Module<0x0C, 4>>  EXTI5;
  typedef EXTI<Module<0x0C, 8>>  EXTI6;
  typedef EXTI<Module<0x0C, 12>> EXTI7;
  typedef EXTI<Module<0x10, 0>>  EXTI8;
  typedef EXTI<Module<0x10, 4>>  EXTI9;
  typedef EXTI<Module<0x10, 8>>  EXTI10;
  typedef EXTI<Module<0x10, 12>> EXTI11;
  typedef EXTI<Module<0x14, 0>>  EXTI12;
  typedef EXTI<Module<0x14, 4>>  EXTI13;
  typedef EXTI<Module<0x14, 8>>  EXTI14;
  typedef EXTI<Module<0x14, 12>> EXTI15;

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
