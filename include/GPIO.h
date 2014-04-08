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

namespace GPIO
{
  /*static constexpr Port volatile* A { reinterpret_cast<Port volatile*>(0x40020000) };
  static constexpr Port volatile* G { reinterpret_cast<Port volatile*>(0x40021800) };*/

  enum class Port : std::size_t
  {
    G = 0x40021800
  };

  template<Port port>
  class PortType
  {
  public:
    template<uint8_t idx>
    class Pin
    {
      friend PortType;

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
        AF0 = 0x0, AF1, AF2, AF3, AF4,
        AF5, AF6, AF7, AF8, AF9, AF10,
        AF11, AF12, AF13, AF14, AF15
      };

      enum class OutputSpeed : uint32_t
      {
        LowSpeed = 0,
        MediumSpeed,
        FastSpeed,
        HighSpeed
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

  template<Port port>
  static constexpr PortType<port> volatile* const getPort();

};
//END GPIO

#include "../src/GPIO.impl"

#endif /* GPIO_H_ */


