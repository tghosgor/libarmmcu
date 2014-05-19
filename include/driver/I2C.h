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

#ifndef I2C_H_
#define I2C_H_

#include <util.h>

#include <cstdint>

namespace stm32f429
{

class I2C
{
public: //Declarations
  /*enum class Module : uint32_t
  {
    _1 = 0x40005400,
    _2 = 0x40005800,
    _3 = 0x40005C00
  };*/

  util::Module2 _1 {0x40023800 + 0x40, 0x1 <<21, 0x40005400};
  util::Module2 _2 {0x40023800 + 0x40, 0x1 <<22, 0x40005800};
  util::Module2 _3 {0x40023800 + 0x40, 0x1 <<23, 0x40005C00};

public:

public: //Methods
  I2C(util::Module2 const& module);
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
  util::Module2 const& m_module;
};

}

#endif /* I2C_H_ */
