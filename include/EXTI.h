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

#ifndef EXTI_H_
#define EXTI_H_

#include <cstdint>

#include <util.h>

namespace stm32f429
{

class EXTI
{
public:
  enum
  {
    _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19,
    _20, _21, _22
  };

  template<uint8_t line>
  class Line
  {
  public:
    void clearPending();

  };

  static constexpr EXTI volatile* const instance() { return reinterpret_cast<EXTI volatile* const>(0x40013C00); }

  template<uint8_t line>
  static constexpr Line<line> getPeriph() { return Line<line>{}; }


public:
  uint32_t m_IMR;   //Interrupt mask
  uint32_t m_EMR;   //Event mask
  uint32_t m_RTSR;  //Rising trigger selection
  uint32_t m_FTSR;  //Falling trigger selection
  uint32_t m_SWIER; //Software interrupt event
  uint32_t m_PR;    //Pending
};
} //NS stm32f429

#include <impl/EXTI.impl>

#endif /* EXTI_H_ */
