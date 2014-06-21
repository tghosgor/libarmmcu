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

#include <util.hpp>

namespace stm32f429
{

enum : std::size_t
{
  _1 = 0x40010000,
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

class TIM
{
private:
/*  using TIM1  = Module<0x44, 0,  TIM::Periph<TIM::_1 >, TIM::_1 >;
  using TIM2  = Module<0x40, 0,  TIM::Periph<TIM::_2 >, TIM::_2 >;
  using TIM3  = Module<0x40, 1,  TIM::Periph<TIM::_3 >, TIM::_3 >;
  using TIM4  = Module<0x40, 2,  TIM::Periph<TIM::_4 >, TIM::_4 >;
  using TIM5  = Module<0x40, 3,  TIM::Periph<TIM::_5 >, TIM::_5 >;
  using TIM6  = Module<0x40, 4,  TIM::Periph<TIM::_6 >, TIM::_6 >;
  using TIM7  = Module<0x40, 5,  TIM::Periph<TIM::_7 >, TIM::_7 >;
  using TIM8  = Module<0x44, 1,  TIM::Periph<TIM::_8 >, TIM::_8 >;
  using TIM9  = Module<0x44, 16, TIM::Periph<TIM::_9 >, TIM::_9 >;
  using TIM10 = Module<0x44, 17, TIM::Periph<TIM::_10>, TIM::_10>;
  using TIM11 = Module<0x44, 18, TIM::Periph<TIM::_11>, TIM::_11>;
  using TIM12 = Module<0x40, 6,  TIM::Periph<TIM::_12>, TIM::_12>;
  using TIM13 = Module<0x40, 7,  TIM::Periph<TIM::_13>, TIM::_13>;
  using TIM14 = Module<0x40, 8,  TIM::Periph<TIM::_14>, TIM::_14>;*/

  using Module = util::Module2<TIM, 1>;

public:
  static const Module TIM1;
  static const Module TIM2;
  static const Module TIM3;
  static const Module TIM4;
  static const Module TIM5;

  enum class UEVSource
  { };

  enum class MasterMode : uint32_t
  {
    Reset = 0x0,
    Enable = 0x1,
    Update = 0x2
  };

  class CC
  {
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

  public:
    CC(volatile TIM& tim, const uint8_t& idx);
    ~CC();

    void enable() volatile;
    void disable() volatile;
    void setValue(uint32_t const value) volatile;
    void setOCMode(OCMode const mode) volatile;
    void enableOCPreload() volatile;
    void disableOCPreload() volatile;

  private:
    volatile TIM& m_tim;
    const uint8_t m_idx;
  };
public: // TIM methods
  TIM(const Module& module);
  ~TIM();

  /* Counter is automatically disabled in one-pulse mode, when an update event occurs. */
  void enable() volatile;
  void disable() volatile;

  void setAutoReloadValue(uint16_t const value) volatile;
  void setPrescalerValue(uint16_t const value) volatile;

  uint16_t getCounterValue() volatile;
  void setCounterValue(uint16_t const value) volatile;

  CC enableCC(const uint8_t& idx) volatile;

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
  struct Registers
  {
    uint32_t m_CR[2];
    uint32_t m_SMCR;
    uint32_t m_DIER;
    uint32_t m_SR;
    uint32_t m_EGR;
    uint32_t m_CCMR[2]; //Capture/Compare Registers
    uint32_t m_CCER;
    uint32_t m_CNT;   //Counter Register
    uint32_t m_PSC;   //Prescaler Register
    uint32_t m_ARR;   //Auto-Reload Register
    uint32_t m_RCR;
    uint32_t m_CCR[4];
    uint32_t m_BDTR;
    uint32_t m_DCR;
    uint32_t m_DMAR;
    uint32_t m_OR;
  };
  static_assert(sizeof(Registers) == 0x54, "TIM size is not correct. Spec says 0x54 bytes.");

public:
  Registers* m_registers;

private:
  const Module& m_module;
};

} //NS stm32f429

#endif /* TIM_H_ */
