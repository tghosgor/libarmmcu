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

#include <cstdint>
#include <functional>

namespace stm32f429
{
namespace util
{

template<std::size_t rccAddr_, uint8_t rccVal_, class T = void, std::size_t moduleAddr_ = 0>
struct Module
{
  static constexpr uint32_t rccAddr = rccAddr_;
  static constexpr uint8_t rccVal = rccVal_;

  typedef T RegType;
  static constexpr std::size_t regAddress = moduleAddr_;
};

template<class T, std::size_t N>
struct Module2
{
  using EnablePair = std::pair<const std::size_t, const uint32_t>;
  using EnablePairList = std::array<EnablePair, N>;

  uint32_t* const m_moduleAddress;
  const EnablePairList m_enablePairs;

  template<typename... E>
  Module2(const std::size_t moduleAddress, E... e)
    : m_moduleAddress(reinterpret_cast<uint32_t* const>(moduleAddress))
    , m_enablePairs{e...}
  { }

  void enable() const
  {
    for(const auto& it : m_enablePairs)
      *reinterpret_cast<uint32_t* const>(it.first) |= it.second;
  }

  void disable() const
  {
    for(const auto& it : m_enablePairs)
      *reinterpret_cast<uint32_t* const>(it.first) &= ~it.second;
  }

  bool isEnabled() const
  {
    //the first one must be enabler (RCC)
    if( (*reinterpret_cast<uint32_t* const>(m_enablePairs[0].first) & m_enablePairs[0].second) != 0 )
      return true;
    else
      return false;
  }

  friend bool operator==(const Module2& lhs, const Module2& rhs)
  {
    return &lhs == &rhs;
  }
};


} //NS util
} //NS stm32f429

#endif /* UTIL_H */
