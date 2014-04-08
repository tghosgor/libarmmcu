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
    template<uint8_t m_idx>
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

      void setMode(Mode const mode);

      void set();
      void reset();

      bool getInputState();
      bool getOutputState();
    }; //END Pin

    template<uint8_t m_idx>
    Pin<m_idx>* getPin() volatile;

  public:
  //private:
    uint32_t m_MODER;
    uint32_t m_OTYPER;
    uint32_t m_OSPEEDER;
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


