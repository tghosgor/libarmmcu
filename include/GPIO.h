/*
 * GPIO.h
 *
 *  Created on: Apr 2, 2014
 *      Author: Tolga HOŞGÖR
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
  PortA = 0x40020000,
  PortB = 0x40020400,
  PortC = 0x40020800,
  PortG = 0x40021800
};

template<std::size_t port>
class Port
{
public:
  template<uint8_t idx>
  class Pin
  {
    friend Port;

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

template<std::size_t port>
constexpr Port<port> volatile* const getPort();

} //NS GPIO
} //NS stm32f429


#include "../src/GPIO.impl"

#endif /* GPIO_H_ */


