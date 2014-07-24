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

#ifndef UTIL_H
#define UTIL_H

#include <functional>
#include <cstdint>
#include <initializer_list>

namespace stm32f429 {
namespace util {

typedef std::pair<unsigned long, unsigned long> AddressValuePair;

template<std::size_t N>
class Module {
public:
  Module(unsigned long moduleRegister, std::initializer_list<AddressValuePair> l)
    : m_moduleRegister(reinterpret_cast<unsigned long*>(moduleRegister))
  {
    for (std::size_t i = 0; i < m_pairList.size(); ++i) {
      m_pairList[i] = *(l.begin() + i);
    }
  }

public:
  void enable() const {
    *reinterpret_cast<unsigned long*>(m_pairList[0].first) |= m_pairList[0].second;
  }
  void disable() const {
    *reinterpret_cast<unsigned long*>(m_pairList[0].first) &= ~m_pairList[0].second;
  }
  bool isEnabled() const {
    return (*reinterpret_cast<unsigned long*>(m_pairList[0].first) & m_pairList[0].second) == m_pairList[0].second;
  }

private:
  unsigned long* const m_moduleRegister;
  std::array<AddressValuePair, N> m_pairList;
};

typedef std::function<bool()> ISR;

}
} //NS stm32f429

#endif /* UTIL_H */
