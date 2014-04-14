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
namespace EXTI
{

class Pending
{
public:
  enum : uint32_t
  {
    _0, _1, _2, _3, _4,
    _5, _6, _7, _8, _9,
    _10, _11, _12, _13, _14,
    _15, _16, _17, _18, _19,
    _20, _21, _22
  };
  /*typedef Module<0x14, 0> _0;
  typedef Module<0x14, 1> _1;
  typedef Module<0x14, 2> _2;
  typedef Module<0x14, 3> _3;
  typedef Module<0x14, 4> _4;
  typedef Module<0x14, 5> _5;
  typedef Module<0x14, 6> _6;
  typedef Module<0x14, 7> _7;
  typedef Module<0x14, 8> _8;
  typedef Module<0x14, 9> _9;
  typedef Module<0x14, 10> _10;
  typedef Module<0x14, 11> _11;
  typedef Module<0x14, 12> _12;
  typedef Module<0x14, 13> _13;
  typedef Module<0x14, 14> _14;
  typedef Module<0x14, 15> _15;
  typedef Module<0x14, 16> _16;
  typedef Module<0x14, 17> _17;
  typedef Module<0x14, 18> _18;
  typedef Module<0x14, 19> _19;
  typedef Module<0x14, 20> _20;
  typedef Module<0x14, 21> _21;
  typedef Module<0x14, 22> _22;*/
};

template<class Module>
class Register;

template<>
class Register<Pending>
{
public:
  template<uint8_t bit>
  void clear();
};

class EXTI
{
public:
  uint32_t m_IMR;   //Interrupt mask
  uint32_t m_EMR;   //Event mask
  uint32_t m_RTSR;  //Rising trigger selection
  uint32_t m_FTSR;  //Falling trigger selection
  uint32_t m_SWIER; //Software interrupt event
  uint32_t m_PR;    //Pending
};

constexpr EXTI volatile* const instance() { return reinterpret_cast<EXTI volatile* const>(0x40013C00); }

template<class Module>
constexpr Register<Module> getReg() { return Register<Module>{}; }

} //NS EXTI
} //NS stm32f429

#include <impl/EXTI.impl>

#endif /* EXTI_H_ */
