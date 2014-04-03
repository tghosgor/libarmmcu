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
  enum class Port
  {
    A = 0x40020000,
    G = 0x40021800
  };

  static GPIO* get(Port port) { return reinterpret_cast<GPIO*>(port); }

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

};

#endif /* GPIO_H_ */
