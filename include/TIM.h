/*
 * TIM.h
 *
 *  Created on: Apr 5, 2014
 *      Author: Tolga HOŞGÖR
 */

#ifndef TIM_H_
#define TIM_H_

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

  static TIM volatile* const getTIM(TIM volatile* const tim);

  /* Counter is automatically disabled in one-pulse mode, when an update event occurs. */
  void enable() volatile;
  void disable() volatile;
  template<uint8_t CCChannel>
  void enableCC() volatile;
  template<uint8_t CCChannel>
  void disableCC() volatile;

  void setAutoReloadValue(uint16_t const value) volatile;
  void setPrescalerValue(uint16_t const value) volatile;
  template<uint8_t CCChannel>
  void setCCValue(uint32_t const value) volatile;

  void setCounterValue(uint16_t const value) volatile;
  uint16_t getCounterValue() volatile;

  void enableUEV() volatile;
  void disableUEV() volatile;
  void setUEVSource(UEVSource const source) volatile;

  void enableOnePulseMode() volatile;
  void disableOnePulseMode() volatile;

  void enableAutoReloadPreload() volatile;
  void disableAutoReloadPreload() volatile;

  void setMasterMode(MasterMode const mode) volatile;

  template<uint8_t CCChannel>
  void setOCMode(OCMode const mode) volatile;
  template<uint8_t CCChannel>
  void enableOCPreload() volatile;

  void enableUpdateDMARequest() volatile;
  void disableUpdateDMARequest() volatile;
  void enableUpdateInterrupt() volatile;
  void disableUpdateInterrupt() volatile;

  bool getStatus() volatile;
  void clearStatus() volatile;

  void generateEvent() volatile;

  static constexpr TIM volatile* _1  { reinterpret_cast<TIM volatile*>(0x40010400) };
  static constexpr TIM volatile* _2  { reinterpret_cast<TIM volatile*>(0x40000000) };
  static constexpr TIM volatile* _3  { reinterpret_cast<TIM volatile*>(0x40000400) };
  static constexpr TIM volatile* _4  { reinterpret_cast<TIM volatile*>(0x40000800) };
  static constexpr TIM volatile* _5  { reinterpret_cast<TIM volatile*>(0x40000C00) };
  static constexpr TIM volatile* _6  { reinterpret_cast<TIM volatile*>(0x40001000) };
  static constexpr TIM volatile* _7  { reinterpret_cast<TIM volatile*>(0x40001400) };
  static constexpr TIM volatile* _8  { reinterpret_cast<TIM volatile*>(0x40010000) };
  static constexpr TIM volatile* _9  { reinterpret_cast<TIM volatile*>(0x40014000) };
  static constexpr TIM volatile* _10 { reinterpret_cast<TIM volatile*>(0x40014400) };
  static constexpr TIM volatile* _11 { reinterpret_cast<TIM volatile*>(0x40014800) };
  static constexpr TIM volatile* _12 { reinterpret_cast<TIM volatile*>(0x40001800) };
  static constexpr TIM volatile* _13 { reinterpret_cast<TIM volatile*>(0x40001C00) };
  static constexpr TIM volatile* _14 { reinterpret_cast<TIM volatile*>(0x40002000) };

protected:
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

static_assert(sizeof(TIM) == 0x54, "TIM size is not correct. Spec says 54 bytes.");

#include "../src/TIM.impl"

#endif /* TIM_H_ */
