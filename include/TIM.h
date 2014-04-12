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

#ifndef TIM_H_
#define TIM_H_

namespace stm32f429
{
namespace TIM
{

enum : std::size_t
{
  _1 = 0x40010400,
  _2 = 0x40000000,
  _3 = 0x40000400,
  _4 = 0x40000800,
  _5 = 0x40000C00,
  _6 = 0x40001000,
  _7 = 0x40001400,
  _8 = 0x40010000,
  _9 = 0x40014000,
  _10 = 0x40014400,
  _11 = 0x40014800,
  _12 = 0x40001800,
  _13 = 0x40001C00,
  _14 = 0x40002000
};

template<std::size_t tim>
class TIM
{
public:
  enum class UEVSource
  {

  };

  enum class MasterMode : uint32_t
  {
    Reset = 0x0,
    Enable = 0x1,
    Update = 0x2
  };

  template<uint8_t idx>
  class CC
  {
    friend TIM;

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
  };

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
  void setUEVSource(UEVSource const source) volatile;

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

static_assert(sizeof(TIM<0>) == 0x54, "TIM size is not correct. Spec says 54 bytes.");

template<std::size_t tim>
constexpr TIM<tim> volatile* const getTIM();

} //NS TIM
} //NS stm32f429

#include "impl/TIM.impl"

#endif /* TIM_H_ */
