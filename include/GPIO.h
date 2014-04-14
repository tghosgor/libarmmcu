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

#ifndef GPIO_H_
#define GPIO_H_

#include <cstdint>
#include <type_traits>

namespace stm32f429
{
namespace GPIO
{

enum : std::size_t
{
  A = 0x40020000,
  B = 0x40020400,
  C = 0x40020800,
  G = 0x40021800
};

template<std::size_t module>
class Periph
{
public:
  template<uint8_t idx>
  class Pin
  {
    friend class Periph;

  public:
    enum class Mode
    {
      Input = 0x0,
      Output = 0x1,
      Alternate = 0x2,
      Analog = 0x3
    };

    enum class AF : uint32_t
    {
      _0 = 0x0,
      _1,
      _2,
      _3,
      _4,
      _5,
      _6,
      _7,
      _8,
      _9,
      _10,
      _11,
      _12,
      _13,
      _14,
      _15
    };

    enum class OutputSpeed : uint32_t
    {
      Low = 0,
      Medium,
      Fast,
      High
    };

    enum class PushPullMode : uint32_t
    {
      None = 0x0,
      PullUp = 0x1,
      PullDown = 0x2
    };

    void setMode(Mode const mode) volatile;
    void setAF(AF const af) volatile;
    void setOutputSpeed(OutputSpeed const ospeed) volatile;
    void setPushPullMode(PushPullMode const ppm) volatile;

    void set() volatile;
    void reset() volatile;

    bool getInputState() volatile;
    bool getOutputState() volatile;

  private:
    template<uint8_t idx_>
    typename std::enable_if<(idx_ < 8)>::type
    setAF_(AF const af) volatile;

    template<uint8_t idx_>
    typename std::enable_if<(idx_ >= 8 && idx_ <= 15)>::type
    setAF_(AF const af) volatile;
  }; //END Pin

  template<uint8_t idx>
  Pin<idx> getPin() volatile;

private:
  uint32_t m_MODER;
  uint32_t m_OTYPER;
  uint32_t m_OSPEEDR;
  uint32_t m_PUPDR;
  uint32_t m_IDR;
  uint32_t m_ODR;
  uint32_t m_BSRR;
  uint32_t m_LCKR;
  uint32_t m_AFRL;
  uint32_t m_AFRH;
}; //END Port

template<std::size_t module>
constexpr Periph<module> volatile* const getPeriph();

} //NS GPIO
} //NS stm32f429

#include "impl/GPIO.impl"

#endif /* GPIO_H_ */


