/*
 * GPIO.h
 *
 *  Created on: Apr 2, 2014
 *      Author: Tolga HOŞGÖR
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <cstddef>
#include <cstdint>
#include <type_traits>

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
        _0 = 0x0, _1, _2, _3, _4,
        _5, _6, _7, _8, _9, _10,
        _11, _12, _13, _14, _15
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

      void setMode(Mode const mode);
      void setAF(AF const af);
      void setOutputSpeed(OutputSpeed const ospeed);
      void setPushPullMode(PushPullMode const ppm);

      void set();
      void reset();

      bool getInputState();
      bool getOutputState();

    private:
      template<uint8_t Enabler>
      typename std::enable_if<(Enabler < 8)>::type
      setAF_(AF const af)
      {
        constexpr uint32_t shiftBy { idx * 4 };
        reinterpret_cast<GPIO::Port<port> volatile*>(port)->m_AFRL &= ~(0x4 <<shiftBy);
        reinterpret_cast<GPIO::Port<port> volatile*>(port)->m_AFRL |= static_cast<uint32_t>(af) <<shiftBy;
      }

      template<uint8_t Enabler>
      typename std::enable_if<(Enabler >= 8 && Enabler <= 15)>::type
      setAF_(AF const af)
      {
        constexpr uint32_t shiftBy { idx * 4 };
        reinterpret_cast<GPIO::Port<port> volatile*>(port)->m_AFRH &= ~(0x4 <<shiftBy);
        reinterpret_cast<GPIO::Port<port> volatile*>(port)->m_AFRH |= static_cast<uint32_t>(af) <<shiftBy;
      }
    }; //END Pin

    template<uint8_t idx>
    Pin<idx>* getPin() volatile;

  public:
  //private:
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

};
//END GPIO

#include "../src/GPIO.impl"

#endif /* GPIO_H_ */


