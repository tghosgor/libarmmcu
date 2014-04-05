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

  static TIM volatile* const getTIM(TIM volatile* const tim);

  /* Counter is automatically disabled in one-pulse mode, when an update event occurs. */
  void enable() volatile;
  void disable() volatile;

  void setAutoReloadValue(uint16_t value) volatile;
  void setPrescalerValue(uint16_t value) volatile;

  void enableUEV() volatile;
  void disableUEV() volatile;
  void setUEVSource(UEVSource) volatile;

  void enableOnePulseMode() volatile;
  void disableOnePulseMode() volatile;

  void enableAutoReloadPreload() volatile;
  void disableAutoReloadPreload() volatile;

  uint16_t getCounterValue() volatile;

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
  uint32_t m_CCMR1;
  uint32_t m_CCMR2;
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

#include "../src/TIM.impl"

#endif /* TIM_H_ */
