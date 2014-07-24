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

#ifndef I2C_H_
#define I2C_H_

#include "include/driver/util.hpp"

#include <cstdint>

namespace stm32f429
{

/*class I2C
{
public: //Declarations

  static constexpr Module _1 {0x40023800 + 0x40, 0x1 <<21, 0x40005400};
  static constexpr Module _2 {0x40023800 + 0x40, 0x1 <<22, 0x40005800};
  static constexpr Module _3 {0x40023800 + 0x40, 0x1 <<23, 0x40005C00};

public:

public: //Methods
  I2C(const Module& module);
  I2C(I2C&& other);
  ~I2C();

  bool const isValid() { return m_isValid; }

private: //Registers
  struct Registers
  {
    uint32_t m_CR1; //control register 1
    uint32_t m_CR2; //control register 2
    uint32_t m_OAR1; //own address register 1
    uint32_t m_OAR2; //own address register 2
    uint32_t m_DR; //data register
    uint32_t m_SR1; //status register 1
    uint32_t m_SR2; //status register 2
    uint32_t m_CCR; //clock control register
    uint32_t m_TRISE;
    uint32_t m_FLTR;
  };

public:
  Registers* m_registers;

private:
  bool m_isValid;
  util::Module<I2C> const& m_module;
};*/

}

#endif /* I2C_H_ */
