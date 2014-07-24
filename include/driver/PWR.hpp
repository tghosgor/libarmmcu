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

#ifndef PWR_H_
#define PWR_H_

#include <cstdint>

namespace stm32f429
{

class PWR
{
public:
  uint32_t static constexpr BaseAddress{ 0x40007000 };

public:
  void disableBDWriteProtection() volatile;
  void enableBDWriteProtection() volatile;

public: //Registers
  uint32_t m_CR; //Power control register
  uint32_t m_CSR; //Power control status register
};

}

#endif /* RTC_H_ */
