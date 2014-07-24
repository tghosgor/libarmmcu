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

#ifndef RCC_H_
#define RCC_H_

#include "include/driver/PLL.hpp"
#include "include/driver/SYSCFG.hpp"
#include "include/driver/TIM.hpp"

#include "include/driver/fwd.hpp"
#include "include/driver/util.hpp"

#include <cstdint>

namespace stm32f429
{

class RCC
{
public:
  static constexpr std::size_t BaseAddress{ 0x40023800 };

public: //Declarations
  //using SYSCFG = Module<0x44, 14, stm32f429::SYSCFG, stm32f429::SYSCFG::BaseAddress>;

  //using LTDC = Module<0x44, 26, LCD, 0x40016800>;

  //using PWR = Module<0x40, 28, stm32f429::PWR, 0x40007000>;

  //using RTC = Module<0x70, 15, stm32f429::RTC, 0x40002800>;

  //using SPI1 = Module<0x44, 12, SPI, 0x40013000>;
  //using SPI5 = Module<0x44, 20, SPI, 0x40015000>;

  enum class PLLSAIDiv : uint32_t
  {
    _2 = 0,
    _4 = 1,
    _8 = 2,
    _16 = 3
  };

public: //Methods
  RCC() = delete;

  static constexpr RCC volatile* const instance();

  template<class Module>
  static typename Module::RegType volatile* enablePeriph();

  bool isPLLSAILocked() volatile
  {
    return m_CR & (0x1 <<29);
  }

  void enablePLLSAI(uint8_t const LCDDivision, uint8_t const SAI1Division, uint16_t const VCODivision, PLLSAIDiv const LCDClkDivision) volatile
  {
    m_PLLSAICFGR &= ~(0x01FF <<6 | 0x0F <<24 | 0x07 <<28);
    m_PLLSAICFGR |= (VCODivision & 0x01FF <<6) <<6 | (SAI1Division & 0x0F) <<24 | (LCDDivision & 0x07) <<28;
    m_DCKCFGR &= ~(0x3 <<16);
    m_DCKCFGR |= static_cast<uint32_t>(LCDClkDivision) <<16;
    m_CR |= 0x1 <<28;
  }

  void disablePLLSAI() volatile
  {
    m_CR &= ~(0x1 <<28);
  }

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
  uint32_t m_PLLSAICFGR;
  uint32_t m_DCKCFGR;
};

static_assert(sizeof(RCC) == 0x90, "RCC size is wrong. Spec says its 0x8C bytes long.");

} //NS stm32f429

#endif /* RCC_H_ */
