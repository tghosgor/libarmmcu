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

#ifndef UTIL_H
#define UTIL_H

#include <functional>

namespace stm32f429
{

namespace util
{

template<uint32_t ...values>
struct EnableSequence
{
  constexpr EnableSequence() { }

  template<uint32_t addr, uint32_t val, uint32_t ...restValues>
  void static run()
  {
    *reinterpret_cast<uint32_t volatile*>(addr) = val;
    run<restValues...>();
  };
};

template<std::size_t rccAddr_, uint8_t rccVal_, class T = void, std::size_t moduleAddr_ = 0>
struct Module
{
  static constexpr uint32_t rccAddr = rccAddr_;
  static constexpr uint8_t rccVal = rccVal_;

  typedef T RegType;
  static constexpr std::size_t regAddress = moduleAddr_;
};

struct Module2
{
  uint32_t* const m_rccAddr;
  const uint32_t m_rccVal;
  void* m_moduleAddr;

  Module2(const std::size_t rccAddr, const uint32_t val, const std::size_t moduleAddr)
    : m_rccAddr(reinterpret_cast<decltype(m_rccAddr)>(rccAddr))
    , m_rccVal(val)
    , m_moduleAddr(reinterpret_cast<decltype(m_moduleAddr)>(moduleAddr))
  {}
};

inline bool operator==(const Module2& lhs, const Module2& rhs)
{
  return &lhs == &rhs;
}

typedef std::function<bool()> ISR;

}

} //NS stm32f429

#endif /* UTIL_H */
