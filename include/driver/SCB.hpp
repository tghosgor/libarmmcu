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

#ifndef SCB_H_
#define SCB_H_

namespace stm32f429
{

class SCB
{
public:
  static constexpr std::size_t BaseAddress{ 0xE000E008 };

public:
  SCB() = delete;

  static volatile SCB* const instance() { return reinterpret_cast<volatile SCB*>(BaseAddress); }

public: //Registers
  uint32_t m_ACTLR;
  uint8_t PADDING1[3316];
  uint32_t m_CPUID;
  uint32_t m_ICSR;  //Interrupt Control and State
  uint32_t m_VTOR;  //Vector Table Offset
  uint32_t m_AIRCR; //Application Interrupt and Reset Control
  uint32_t m_SCR;   //System Control
  uint32_t m_CCR;   //Configuration and Control
  uint32_t m_SHPR1; //System Handler Priority 1
  uint32_t m_SHPR2; //System Handler Priority 2
  uint32_t m_SHPR3; //System Handler Priority 3
  uint32_t m_SHCRS; //System Handler Control and State
  uint32_t m_CFSR;  //Configurable Fault Status
  uint32_t m_HFSR;  //HardFault Status
  uint8_t PADDING2[1];
  uint32_t m_MMAR;  //MemManage Fault Address
  uint32_t m_BFAR;  //BusFault Address
  uint32_t m_AFSR;  //Auxiliary Fault
};

static_assert(sizeof(SCB) == (0xE000ED3C - SCB::BaseAddress) + 4, "SCB size is wrong.");

} //NS stm32f429

#endif /* SCB_H_ */
