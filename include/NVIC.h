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

#ifndef NVIC_H_
#define NVIC_H_

#include <cstddef> //offsetof
#include <cstdint>

namespace stm32f429
{

class NVIC
{
public: //Declarations
  template<uint8_t N>
  class Interrupt
  {
  public:
    void enable();
    void disable();
    void setPending();
    void clearPending();
    void isActive();
    void setPriority();
    void triggerSoftwareInterrupt();
  };

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
  template<uint8_t N>
  static constexpr Interrupt<N> getReg() { return Interrupt<N>{}; }

public:
  static constexpr std::size_t BaseAddress{ 0xE000E100 };
};

static_assert(offsetof(NVIC, m_ICER[7]) == 0xE000E19C - NVIC::BaseAddress, "Test?");
static_assert(sizeof(NVIC) == (0xE000EF00 - NVIC::BaseAddress) + 4, "NVIC size is wrong.");

} //NS stm32f429

#include <impl/NVIC.impl>

#endif /* NVIC_H_ */
