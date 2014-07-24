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

#ifndef SYSCFG_H_
#define SYSCFG_H_

#include <cstddef>
#include <cstdint>
#include <type_traits>

#include "include/driver/EXTI.hpp"
#include "include/driver/NVIC.hpp"

#include "include/driver/util.hpp"

namespace stm32f429
{

/*class SYSCFG
{
  friend class RCC;

public:
  static constexpr std::size_t BaseAddress{ 0x40013800 };

private: //Internal Declarations
  template<uint8_t N>
  using EXTIModule = util::Module<BaseAddress + 0x08 + (N / 4) * 0x4, (N * 4) % 16, stm32f429::EXTI<N>, stm32f429::EXTI<N>::BaseAddress>;

  template<std::size_t bit, class T>
  using NVICEXTIModule = util::Module<NVIC::BaseAddress + offsetof(NVIC, m_ISER) + bit / 32, bit % 32, T, BaseAddress>;

public: //Declarations
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

  using EXTI0 = NVICEXTIModule<6 , EXTI<EXTIModule<0>>>;
  using EXTI1 = NVICEXTIModule<7 , EXTI<EXTIModule<1>>>;
  using EXTI2 = NVICEXTIModule<8 , EXTI<EXTIModule<2>>>;
  using EXTI3 = NVICEXTIModule<9 , EXTI<EXTIModule<3>>>;
  using EXTI4 = NVICEXTIModule<10, EXTI<EXTIModule<4>>>;

public:
  static constexpr SYSCFG volatile* const instance();

  template<class Module>
  typename Module::RegType volatile* enable() volatile;

public:
  uint32_t m_MEMRM;     //Memory Remap
  uint32_t m_PMC;       //Peripheral Mode Configuration
  uint32_t m_EXTICR[4]; //External Interrupt Configuration N
  uint32_t m_CMPCR;     //Compensation Cell Control

private:
  SYSCFG() { }
};*/

} //NS stm32f429

#endif /* SYSCFG_H_ */
