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

#ifndef EXTI_H_
#define EXTI_H_

#include "include/driver/util.hpp"

#include <cstdint>
#include <functional>

namespace stm32f429
{

template<uint8_t line>
class EXTI
{
public:
  static constexpr std::size_t BaseAddress{ 0x40013C00 };

public: //Declarations
  EXTI() = delete;

public: //Methods
  void registerISR(bool (*f)()) volatile;
  void enableInterrupt() volatile;
  void disableInterrupt() volatile;
  void enableRisingTrigger() volatile;
  void disableRisingTrigger() volatile;
  void enableFallingTrigger() volatile;
  void disableFallingTrigger() volatile;
  void generateSoftwareInterrupt() volatile;
  bool isPending() volatile;
  void clearPending() volatile;

public:
  uint32_t m_IMR;   //Interrupt mask
  uint32_t m_EMR;   //Event mask
  uint32_t m_RTSR;  //Rising trigger selection
  uint32_t m_FTSR;  //Falling trigger selection
  uint32_t m_SWIER; //Software interrupt event
  uint32_t m_PR;    //Pending
};

} //NS stm32f429

#endif /* EXTI_H_ */
