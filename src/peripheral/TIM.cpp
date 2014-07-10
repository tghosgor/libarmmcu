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

#include <peripheral/TIM.hpp>

#include <exception.hpp>

namespace stm32f429
{

const TIM::Module TIM::TIM1 { 0x40010000, std::make_pair(0x40023800 + 0x30, 0x1 <<0) };
const TIM::Module TIM::TIM2 { 0x40000000, std::make_pair(0x40023800 + 0x30, 0x1 <<0) };
const TIM::Module TIM::TIM3 { 0x40000400, std::make_pair(0x40023800 + 0x30, 0x1 <<0) };
const TIM::Module TIM::TIM4 { 0x40000800, std::make_pair(0x40023800 + 0x30, 0x1 <<0) };
const TIM::Module TIM::TIM5 { 0x40000C00, std::make_pair(0x40023800 + 0x30, 0x1 <<0) };

TIM::TIM(const TIM::Module& module)
  : m_module(module)
{
  if(module.isEnabled())
    throw exception::Error("Port is already enabled.");
  m_registers = reinterpret_cast<Registers* const>(module.m_moduleAddress);
  module.enable();
}

TIM::~TIM()
{
  m_module.disable();
}

void TIM::enable() volatile
{
  m_registers->m_CR[0] |= 0x1;
}

void TIM::disable() volatile
{
  m_registers->m_CR[0] &= ~0x1;
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

TIM::CC TIM::enableCC(const uint8_t& idx) volatile
{
  return TIM::CC(*this, idx);
}

void TIM::enableUEV() volatile
{
  m_registers->m_CR[0] |= (0x1 <<1);
}

void TIM::disableUEV() volatile
{
  m_registers->m_CR[0] &= ~(0x1 <<1);
}

void TIM::setUEVSource(UEVSource const uEVSource) volatile
{
}

void TIM::enableOnePulseMode() volatile
{
  m_registers->m_CR[0] |= 0x1 <<2;
}

void TIM::disableOnePulseMode() volatile
{
  m_registers->m_CR[0] &= ~(0x1 <<2);
}

void TIM::enableAutoReloadPreload() volatile
{
  m_registers->m_CR[0] |= 0x1 <<7;
}

void TIM::disableAutoReloadPreload() volatile
{
  m_registers->m_CR[0] &= ~(0x1 <<7);
}

void TIM::setMasterMode(TIM::MasterMode const mode) volatile
{
  auto newCR = m_registers->m_CR[1]; //TODO: BURADAKİ TEMP GEREKLİ Mİ?
  newCR &= ~(0x7 <<4);
  newCR |= static_cast<uint32_t>(mode) <<4;
  m_registers->m_CR[1] = newCR;
}

TIM::CC::CC(volatile TIM& tim, const uint8_t& idx)
  : m_tim(tim)
  , m_idx(idx)
{
  m_tim.m_registers->m_CCER |= 0x1 <<((m_idx - 1) * 4);
}

TIM::CC::~CC()
{
  m_tim.m_registers->m_CCER &= ~(0x1 <<((m_idx - 1) * 4));
}

void TIM::CC::setValue(const uint32_t value) volatile
{
  volatile uint32_t& CCR1 = m_tim.m_registers->m_CCR[m_idx - 1];
  CCR1 = value;
}

void TIM::CC::setOCMode(TIM::CC::OCMode const mode) volatile
{
  const uint8_t shiftBy = 4 + (m_idx % 3) * 8;
  auto& ccmr = m_tim.m_registers->m_CCMR[m_idx / 3];
  ccmr &= ~(0x7 <<shiftBy);
  ccmr |= static_cast<uint32_t>(mode) <<shiftBy;
}

void TIM::CC::enableOCPreload() volatile
{
  const uint8_t shiftBy{ 3 + (m_idx % 3) * 8};
  auto& ccmr = m_tim.m_registers->m_CCMR[m_idx / 3];
  ccmr |= 0x1 <<shiftBy;
}
void TIM::CC::disableOCPreload() volatile
{
  const uint8_t shiftBy{ 3 + (m_idx % 3) * 8};
  auto& ccmr = m_tim.m_registers->m_CCMR[m_idx / 3];
  ccmr &= ~(0x1 <<shiftBy);
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
