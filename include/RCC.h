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
using util::Module;

class RCC
{
public: //Declarations
  template<class Module>
  class GPIO;

  using GPIOA = GPIO<Module<0x30, 0>>;
  using GPIOB = GPIO<Module<0x30, 1>>;
  using GPIOC = GPIO<Module<0x30, 2>>;
  using GPIOD = GPIO<Module<0x30, 3>>;
  using GPIOE = GPIO<Module<0x30, 4>>;
  using GPIOF = GPIO<Module<0x30, 5>>;
  using GPIOG = GPIO<Module<0x30, 6>>;

  template<class Module>
  class GPIO
  {
    friend class RCC;

  public: //Methods
    void enable();
    void disable();
    void enableLPMode();
    void disableLPMode();

  private:
    GPIO();
  };

  template<class Module>
  class TIM;

  using TIM1 = TIM<Module<0x44, 0>> ;
  using TIM2 = TIM<Module<0x40, 0>> ;
  using TIM3 = TIM<Module<0x40, 1>> ;
  using TIM4 = TIM<Module<0x40, 2>> ;
  using TIM5 = TIM<Module<0x40, 3>> ;
  using TIM6 = TIM<Module<0x40, 4>> ;
  using TIM7 = TIM<Module<0x40, 5>> ;
  using TIM8 = TIM<Module<0x44, 1>> ;
  using TIM9 = TIM<Module<0x44, 16>>;
  using TIM10 = TIM<Module<0x44, 17>>;
  using TIM11 = TIM<Module<0x44, 18>>;
  using TIM12 = TIM<Module<0x40, 6>> ;
  using TIM13 = TIM<Module<0x40, 7>> ;
  using TIM14 = TIM<Module<0x40, 8>> ;

  template<class Module>
  class TIM
  {
    friend class RCC;

  public: //Methods
    void enable();
    void disable();
    void enableLPMode();
    void disableLPMode();

  private:
    TIM();
  };

public: //Methods
  RCC() = delete;

  static constexpr RCC volatile* const instance();

  template<class Module>
  static constexpr Module getReg();

public: //Registers
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

public:
  static constexpr std::size_t BaseAddress{ 0x40023800 };
};

static_assert(sizeof(RCC) == 0x88, "RCC size is wrong. Spec says its 88 bytes long.");

} //NS stm32f429

#include "impl/RCC.impl"

#endif /* RCC_H_ */
