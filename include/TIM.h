/*
 * TIM.h
 *
 *  Created on: Apr 5, 2014
 *      Author: Tolga HOŞGÖR
 */

#ifndef TIM_H_
#define TIM_H_

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
    setOCMode_(OCMode const mode) volatile
    {
      constexpr uint8_t shiftBy{4 + (idx - 1) * 8};
      auto newCCMR = reinterpret_cast<TIM<tim> volatile*>(tim)->m_CCMR1;
      newCCMR &= ~(0x7 <<shiftBy);
      newCCMR |= static_cast<uint32_t>(mode) <<shiftBy;
      reinterpret_cast<TIM<tim> volatile*>(tim)->m_CCMR1 = newCCMR;
    }

    template<uint8_t idx_>
    typename std::enable_if<(idx_ >= 3 && idx_ <= 4)>::type
    setOCMode_(OCMode const mode) volatile
    {
      constexpr uint8_t shiftBy{4 + (idx - 3) * 8};
      auto newCCMR = reinterpret_cast<TIM<tim> volatile*>(tim)->m_CCMR2;
      newCCMR &= ~(0x7 <<shiftBy);
      newCCMR |= static_cast<uint32_t>(mode) <<shiftBy;
      reinterpret_cast<TIM<tim> volatile*>(tim)->m_CCMR2 = newCCMR;
    }

    template<uint8_t idx_>
    typename std::enable_if<(idx_ >= 1 && idx_ <= 2)>::type
    enableOCPreload_() volatile
    {
      constexpr uint8_t shiftBy{ 3 + (idx - 1) * 8};
      reinterpret_cast<TIM<tim> volatile*>(tim)->m_CCMR1 |= 0x1 <<shiftBy;
    }

    template<uint8_t idx_>
    typename std::enable_if<(idx_ >= 3 && idx_ <= 4)>::type
    enableOCPreload_() volatile
    {
      constexpr uint8_t shiftBy{ 3 + (idx - 3) * 8};
      reinterpret_cast<TIM<tim> volatile*>(tim)->m_CCMR2 |= 0x1 <<shiftBy;
    }
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

#include "../src/TIM.impl"

#endif /* TIM_H_ */
