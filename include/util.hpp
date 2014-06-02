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
  using EnablePairList = std::array<std::pair<const std::size_t, const uint32_t>, N>;

  const std::size_t m_moduleAddress;
  const EnablePairList m_enablePairs;

  void enable()
  {
    for(const auto& it : m_enablePairs)
      it->first |= it->second;
  }

  friend bool operator==(const Module2& lhs, const Module2& rhs)
  {
    return &lhs == &rhs;
  }
};

}

} //NS stm32f429

#endif /* UTIL_H */
