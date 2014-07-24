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

#ifndef IVTABLE_H_
#define IVTABLE_H_

#include "include/driver/util.hpp"

#include <cstdint>
#include <array>

namespace stm32f429
{

extern "C" void Default_Handler();

struct IVTable
{
  uint32_t m_notImplemented[16];
  std::array<void(*)(), 32> m_IRQ;

  IVTable() { std::fill(m_IRQ.begin(), m_IRQ.end(), Default_Handler); }
};

extern IVTable ivTable;

} //NS stm32f429

#endif /* IVTABLE_H_ */
