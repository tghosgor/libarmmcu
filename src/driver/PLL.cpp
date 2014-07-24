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

#include "include/driver/PLL.hpp"

namespace stm32f429
{

void PLL::setMultiplicationFactor(uint16_t const factor) volatile
{
//  m_PLLSAICFGR &= ~(0x01FF <<6);
//  m_PLLSAICFGR |= factor <<6;
}

void PLL::setDivisionFactor(uint8_t const factor) volatile
{
//  m_PLLSAICFGR &= ~(0x07 <<28);
//  m_PLLSAICFGR |= (factor & 0x0F) <<28;
}

bool PLL::isReady() volatile
{
//  return ( *(&m_PLLSAICFGR - 1) ) & (0x1 <<29);
}

} //NS stm32f429
