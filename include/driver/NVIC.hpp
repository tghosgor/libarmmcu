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

#ifndef NVIC_H_
#define NVIC_H_

#include "include/driver/util.hpp"

#include <cstddef>
#include <cstdint>

namespace stm32f429
{

/*class NVIC
{
public:
  static constexpr std::size_t BaseAddress{ 0xE000E100 };

public: //Declarations
  //template<std::size_t offset, uint8_t shift, class T>
  //using Module = util::Module<offset, shift, T, 0x40013C00>;

  using Module = util::Module<2>;

  //incomplete
  using WWDG        = Module<0, 0 , EXTI<0>>;
  using PVD         = Module<0, 1 , EXTI<0>>;
  using TAMP_STAMP  = Module<0, 2 , EXTI<0>>;
  using RTC_WKUP    = Module<0, 3 , EXTI<0>>;
  using FLASH       = Module<0, 4 , EXTI<0>>;
  using RCC         = Module<0, 5 , EXTI<0>>;

  using EXTI0 = EXTIModule<0, 6 , SYSCFG::EXTI<SYSCFG::EXTIModule<0>>>;
  using EXTI1 = EXTIModule<0, 7 , SYSCFG::EXTI<SYSCFG::EXTIModule<1>>>;
  using EXTI2 = EXTIModule<0, 8 , SYSCFG::EXTI<SYSCFG::EXTIModule<2>>>;
  using EXTI3 = EXTIModule<0, 9 , SYSCFG::EXTI<SYSCFG::EXTIModule<3>>>;
  using EXTI4 = EXTIModule<0, 10, SYSCFG::EXTI<SYSCFG::EXTIModule<4>>>;

public: //Methods
  template<class Module>
  static typename Module::RegType volatile* enable();
  template<class Module>
  static void disable();
  template<class Module>
  static void setPending();
  template<class Module>
  static void clearPending();
  template<class Module>
  static void isActive();
  template<class Module>
  static void setPriority();
  template<class Module>
  static void triggerSoftwareInterrupt(); //?

public: //Registers
  uint32_t m_ISER[8];
  uint8_t PADDING1[0x60];
  uint32_t m_ICER[8];
  uint8_t PADDING2[0x60];
  uint32_t m_ISPR[8];
  uint8_t PADDING3[0x60];
  uint32_t m_ICPR[8];
  uint8_t PADDING4[0x60];
  uint32_t m_IABR[8];
  uint8_t PADDING5[0xE0];
  uint32_t m_IPR[60];
  uint8_t PADDING6[0xA0D];
  uint32_t m_STIR;

  //E1D

public:
  NVIC() = delete;

  static volatile NVIC* const instance() { return reinterpret_cast<volatile NVIC*>(BaseAddress); }
};

static_assert(offsetof(NVIC, m_ICER[7]) == 0xE000E19C - NVIC::BaseAddress, "Test?");
static_assert(sizeof(NVIC) == (0xE000EF00 - NVIC::BaseAddress) + 4, "NVIC size is wrong.");*/

} //NS stm32f429

#endif /* NVIC_H_ */
