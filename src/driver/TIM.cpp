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

#ifndef TIm_registers->m_CPP_
#define TIm_registers->m_CPP_

#include "include/driver/TIM.hpp"

namespace stm32f429
{

const TIM::Module TIM::_1 (0x40010000, {{0x40023800 + 0x44, 0x1 <<0}});
const TIM::Module TIM::_2 (0x40000000, {{0x40023800 + 0x40, 0x1 <<0}});
const TIM::Module TIM::_3 (0x40000400, {{0x40023800 + 0x40, 0x1 <<1}});
const TIM::Module TIM::_4 (0x40000800, {{0x40023800 + 0x40, 0x1 <<2}});
const TIM::Module TIM::_5 (0x40000C00, {{0x40023800 + 0x40, 0x1 <<3}});
const TIM::Module TIM::_6 (0x40001000, {{0x40023800 + 0x40, 0x1 <<4}});
const TIM::Module TIM::_7 (0x40001400, {{0x40023800 + 0x40, 0x1 <<5}});
const TIM::Module TIM::_8 (0x40010000, {{0x40023800 + 0x44, 0x1 <<1}});
const TIM::Module TIM::_9 (0x40014000, {{0x40023800 + 0x44, 0x1 <<1}});
const TIM::Module TIM::_10(0x40014400, {{0x40023800 + 0x44, 0x1 <<17}});
const TIM::Module TIM::_11(0x40014800, {{0x40023800 + 0x44, 0x1 <<18}});
const TIM::Module TIM::_12(0x40001800, {{0x40023800 + 0x40, 0x1 <<6}});
const TIM::Module TIM::_13(0x40001C00, {{0x40023800 + 0x40, 0x1 <<7}});
const TIM::Module TIM::_14(0x40002000, {{0x40023800 + 0x40, 0x1 <<8}});

TIM::TIM(const TIM::Module& module) {

}

void TIM::enable() volatile
{
  m_registers->m_CR1 |= 0x1;
}

void TIM::disable() volatile
{
  m_registers->m_CR1 &= ~0x1;
}

void TIM::setAutoReloadValue(uint16_t const value) volatile
{
  m_registers->m_ARR = value;
}

void TIM::setPrescalerValue(uint16_t const value) volatile
{
  m_registers->m_PSC = value;
}

uint16_t TIM::getCounterValue() volatile
{
  return m_registers->m_CNT;
}

template<uint8_t idx>
constexpr TIM::CC<idx> TIM::getCC() volatile
{
  return TIM::CC<idx>{};
}

void TIM::enableUEV() volatile
{
  m_registers->m_CR1 |= (0x1 <<1);
}

void TIM::disableUEV() volatile
{
  m_registers->m_CR1 &= ~(0x1 <<1);
}

void TIM::enableOnePulseMode() volatile
{
  m_registers->m_CR1 |= 0x1 <<2;
}

void TIM::disableOnePulseMode() volatile
{
  m_registers->m_CR1 &= ~(0x1 <<2);
}

void TIM::enableAutoReloadPreload() volatile
{
  m_registers->m_CR1 |= 0x1 <<7;
}

void TIM::disableAutoReloadPreload() volatile
{
  m_registers->m_CR1 &= ~(0x1 <<7);
}

void TIM::setMasterMode(TIM::MasterMode const mode) volatile
{
  auto newCR = m_registers->m_CR2; //TODO: BURADAKİ TEMP GEREKLİ Mİ?
  newCR &= ~(0x7 <<4);
  newCR |= static_cast<uint32_t>(mode) <<4;
  m_registers->m_CR2 = newCR;
}

template<uint8_t idx>
void TIM::CC<idx>::enable() volatile
{
  reinterpret_cast<TIM volatile* const>(module)->m_registers->m_CCER |= 0x1 <<((idx - 1) * 4);
}

template<uint8_t idx>
void TIM::CC<idx>::disable() volatile
{
  reinterpret_cast<TIM volatile* const>(module)->m_registers->m_CCER |= ~(0x1 <<((idx - 1) * 4));
}

template<uint8_t idx>
void TIM::CC<idx>::setValue(uint32_t const value) volatile
{
  constexpr uint32_t volatile* CCR1 = &(reinterpret_cast<TIM volatile* const>(module)->m_registers->m_CCR1);
  *(CCR1 + (idx - 1)) =  value;
}

template<uint8_t idx>
void TIM::CC<idx>::setOCMode(TIM::CC<idx>::OCMode const mode) volatile
{
  setOCMode_<idx>(mode);
}

template<uint8_t idx>
void TIM::CC<idx>::enableOCPreload() volatile
{
  enableOCPreload_<idx>();
}

template<uint8_t idx>
template<uint8_t idx_>
typename std::enable_if<(idx >= 1 && idx_ <= 2)>::type
TIM::CC<idx>::setOCMode_(OCMode const mode) volatile
{
  constexpr uint8_t shiftBy{4 + (idx - 1) * 8};
  auto newCCMR = reinterpret_cast<TIM volatile* const>(module)->m_registers->m_CCMR1;
  newCCMR &= ~(0x7 <<shiftBy);
  newCCMR |= static_cast<uint32_t>(mode) <<shiftBy;
  reinterpret_cast<TIM volatile* const>(module)->m_registers->m_CCMR1 = newCCMR;
}

template<uint8_t idx>
template<uint8_t idx_>
typename std::enable_if<(idx_ >= 3 && idx_ <= 4)>::type
TIM::CC<idx>::setOCMode_(OCMode const mode) volatile
{
  constexpr uint8_t shiftBy{4 + (idx - 3) * 8};
  auto newCCMR = reinterpret_cast<TIM volatile* const>(module)->m_registers->m_CCMR2;
  newCCMR &= ~(0x7 <<shiftBy);
  newCCMR |= static_cast<uint32_t>(mode) <<shiftBy;
  reinterpret_cast<TIM volatile* const>(module)->m_registers->m_CCMR2 = newCCMR;
}

template<uint8_t idx>
template<uint8_t idx_>
typename std::enable_if<(idx_ >= 1 && idx_ <= 2)>::type
TIM::CC<idx>::enableOCPreload_() volatile
{
  constexpr uint8_t shiftBy{ 3 + (idx - 1) * 8};
  reinterpret_cast<TIM volatile* const>(module)->m_registers->m_CCMR1 |= 0x1 <<shiftBy;
}

template<uint8_t idx>
template<uint8_t idx_>
typename std::enable_if<(idx_ >= 3 && idx_ <= 4)>::type
TIM::CC<idx>::enableOCPreload_() volatile
{
  constexpr uint8_t shiftBy{ 3 + (idx - 3) * 8};
  reinterpret_cast<TIM volatile* const>(module)->m_registers->m_CCMR2 |= 0x1 <<shiftBy;
}

void TIM::enableUpdateDMARequest() volatile
{
  m_registers->m_DIER |= 0x1 <<8;
}

void TIM::disableUpdateDMARequest() volatile
{
  m_registers->m_DIER &= ~(0x1 <<8);
}

void TIM::enableUpdateInterrupt() volatile
{
  m_registers->m_DIER |= 0x1;
}

void TIM::disableUpdateInterrupt() volatile
{
  m_registers->m_DIER &= ~0x1;
}

bool TIM::getStatus() volatile
{
  return m_registers->m_SR & 0x1;
}

void TIM::clearStatus() volatile
{
  m_registers->m_SR &= ~0x1;
}

void TIM::generateEvent() volatile
{
  m_registers->m_EGR |= 0x1;
}

} //NS stm32f429

#endif
