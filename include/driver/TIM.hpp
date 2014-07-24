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

#ifndef TIM_H_
#define TIM_H_

#include "include/driver/util.hpp"

namespace stm32f429
{

class TIM
{
public:
  using Module = util::Module<1>;

  static const Module _1;
  static const Module _2;
  static const Module _3;
  static const Module _4;
  static const Module _5;
  static const Module _6;
  static const Module _7;
  static const Module _8;
  static const Module _9;
  static const Module _10;
  static const Module _11;
  static const Module _12;
  static const Module _13;
  static const Module _14;

  enum class MasterMode : uint32_t
  {
    Reset = 0x0,
    Enable = 0x1,
    Update = 0x2
  };

  template<uint8_t idx>
  class CC {
    friend class TIM;

  public:
    enum class OCMode : uint32_t
    {
      Frozen = 0x0,
      ActiveOnMatch = 0x1,
      InactiveOnMatch = 0x2,
      Toggle = 0x3,
      ForceInactive = 0x4,
      ForceActive = 0x5,
      PWM1 = 0x6,
      PWM2 = 0x7
    };

    void enable() volatile;
    void disable() volatile;
    void setValue(uint32_t const value) volatile;
    void setOCMode(OCMode const mode) volatile;
    void enableOCPreload() volatile;

  private:
    template<uint8_t idx_>
    typename std::enable_if<(idx >= 1 && idx_ <= 2)>::type
    setOCMode_(OCMode const mode) volatile;

    template<uint8_t idx_>
    typename std::enable_if<(idx_ >= 3 && idx_ <= 4)>::type
    setOCMode_(OCMode const mode) volatile;

    template<uint8_t idx_>
    typename std::enable_if<(idx_ >= 1 && idx_ <= 2)>::type
    enableOCPreload_() volatile;

    template<uint8_t idx_>
    typename std::enable_if<(idx_ >= 3 && idx_ <= 4)>::type
    enableOCPreload_() volatile;
  };// class CC

public:
  TIM(const Module& module);

  /* Counter is automatically disabled in one-pulse mode, when an update event occurs. */
  void enable() volatile;
  void disable() volatile;

  void setAutoReloadValue(uint16_t const value) volatile;
  void setPrescalerValue(uint16_t const value) volatile;

  uint16_t getCounterValue() volatile;
  void setCounterValue(uint16_t const value) volatile;

  template<uint8_t idx>
  constexpr CC<idx> getCC() volatile;

  void enableUEV() volatile;
  void disableUEV() volatile;
  //void setUEVSource(UEVSource const source) volatile;

  void enableOnePulseMode() volatile;
  void disableOnePulseMode() volatile;

  void enableAutoReloadPreload() volatile;
  void disableAutoReloadPreload() volatile;

  void setMasterMode(MasterMode const mode) volatile;

  void enableUpdateDMARequest() volatile;
  void disableUpdateDMARequest() volatile;
  void enableUpdateInterrupt() volatile;
  void disableUpdateInterrupt() volatile;

  bool getStatus() volatile;
  void clearStatus() volatile;

  void generateEvent() volatile;

private:
  struct Registers {
    uint32_t m_CR1;
    uint32_t m_CR2;
    uint32_t m_SMCR;
    uint32_t m_DIER;
    uint32_t m_SR;
    uint32_t m_EGR;
    uint32_t m_CCMR1; //Capture/Compare Register 1
    uint32_t m_CCMR2; //Capture/Compare Register 2
    uint32_t m_CCER;
    uint32_t m_CNT;   //Counter Register
    uint32_t m_PSC;   //Prescaler Register
    uint32_t m_ARR;   //Auto-Reload Register
    uint32_t m_RCR;
    uint32_t m_CCR1;
    uint32_t m_CCR2;
    uint32_t m_CCR3;
    uint32_t m_CCR4;
    uint32_t m_BDTR;
    uint32_t m_DCR;
    uint32_t m_DMAR;
    uint32_t m_OR;
  };
  static_assert(sizeof(TIM::Registers) == 0x54, "TIM size is not correct. Spec says 0x54 bytes.");

  Registers* m_registers;
};

} //NS stm32f429

#endif /* TIM_H_ */
