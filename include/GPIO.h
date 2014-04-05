/*
 * GPIO.h
 *
 *  Created on: Apr 2, 2014
 *      Author: Tolga HOŞGÖR
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <cstdint>

class GPIO
{
public:
  class Port
  {
  public:
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

      void setMode(Mode const mode);

      void set();
      void reset();

      bool getInputState();
      bool getOutputState();

    private:
      Pin(Port volatile& port, uint8_t const pinIdx);

    private:
      volatile Port& m_port;
      uint8_t m_idx;
    }; //END Pin

    Pin getPin(uint8_t const pin) volatile;

    static constexpr Port volatile* A { reinterpret_cast<Port volatile*>(0x40020000) };
    static constexpr Port volatile* G { reinterpret_cast<Port volatile*>(0x40021800) };

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

  static constexpr Port volatile* const getPort(Port volatile* const port);

};
//END GPIO

#include "../src/GPIO.impl"

#endif /* GPIO_H_ */


