
/*
 * GPIO.cpp
 *
 *  Created on: Apr 4, 2014
 *      Author: Tolga HOŞGÖR
 */

#include <GPIO.h>

void GPIO::setType(uint8_t i)
{
}

void GPIO::set(uint8_t pin)
{
  m_BSSR |= 0x1 <<pin;
}

void GPIO::reset(uint8_t pin)
{
}

volatile GPIO* get(GPIO::Port port)
{
  return reinterpret_cast<volatile GPIO*>(port);
}
