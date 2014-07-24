/*
  Copyright (c) 2014, Tolga HOŞGÖR
  All rights reserved.

  This file is part of libarmmcu.

  libarmmcu is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  libarmmcu is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with libarmmcu.  If not, see <http://www.gnu.org/licenses/>
*/

#include "include/driver/RCC.hpp"

#include "include/driver/GPIO.hpp"

#include <type_traits>

namespace stm32f429
{

const GPIO::Module GPIO::A(0x40020000, {{0x40023800 + 0x30, 0x1 <<0}});
const GPIO::Module GPIO::B(0x40020400, {{0x40023800 + 0x30, 0x1 <<1}});
const GPIO::Module GPIO::C(0x40020800, {{0x40023800 + 0x30, 0x1 <<2}});
const GPIO::Module GPIO::D(0x40020C00, {{0x40023800 + 0x30, 0x1 <<3}});
const GPIO::Module GPIO::E(0x40021000, {{0x40023800 + 0x30, 0x1 <<4}});
const GPIO::Module GPIO::F(0x40021400, {{0x40023800 + 0x30, 0x1 <<5}});
const GPIO::Module GPIO::G(0x40021800, {{0x40023800 + 0x30, 0x1 <<6}});
const GPIO::Module GPIO::H(0x40021C00, {{0x40023800 + 0x30, 0x1 <<7}});
const GPIO::Module GPIO::I(0x40022000, {{0x40023800 + 0x30, 0x1 <<8}});

GPIO::GPIO(const Module& module) {

}

template<class PinType_>
typename PinType_::type GPIO::createPin(uint8_t const nPin, PinType_ const) volatile
{
  const uint32_t shiftBy { (nPin * 2u) };
  m_registers->m_MODER &= ~(0x3u <<shiftBy);
  m_registers->m_MODER |= static_cast<uint32_t>(PinType_::moder) <<shiftBy;

  return typename PinType_::type(nPin, *this);
}

template
decltype(GPIO::InputPin)::type GPIO::createPin(uint8_t const nPin, decltype(GPIO::InputPin) const) volatile;
template
decltype(GPIO::OutputPin)::type GPIO::createPin(uint8_t const nPin, decltype(GPIO::OutputPin) const) volatile;
template
decltype(GPIO::AlternatePin)::type GPIO::createPin(uint8_t const nPin, decltype(GPIO::AlternatePin) const) volatile;
template
decltype(GPIO::AnalogPin)::type GPIO::createPin(uint8_t const nPin, decltype(GPIO::AnalogPin) const) volatile;

GPIO::Pin::Pin(uint8_t const nPin, GPIO volatile& GPIO)
  : m_nPin(nPin)
  , m_GPIO(GPIO)
{ }

GPIO::OuPin::OuPin(uint8_t const nPin, GPIO volatile& GPIO)
  : Pin(nPin, GPIO)
{ }

GPIO::InPin::InPin(uint8_t const nPin, GPIO volatile& GPIO)
  : Pin(nPin, GPIO)
{ }

GPIO::AlPin::AlPin(uint8_t const nPin, GPIO volatile& GPIO)
  : Pin(nPin, GPIO)
{ }

GPIO::AnPin::AnPin(const uint8_t nPin, volatile GPIO& GPIO)
: Pin(nPin, GPIO)
{ }

void GPIO::Pin::setPullMode(typename GPIO::Pin::PullMode const ppm) volatile
{
  const uint32_t shiftBy { m_nPin * 2u };
  m_GPIO.m_registers->m_PUPDR &= ~(0x3u <<shiftBy);
  m_GPIO.m_registers->m_PUPDR |= static_cast<uint32_t>(ppm) <<shiftBy;
}

GPIO::OuPin volatile& GPIO::OuPin::setOutputSpeed(GPIO::OuPin::OutputSpeed const ospeed) volatile
{
  const uint32_t shiftBy { m_nPin * 2u };
  m_GPIO.m_registers->m_OSPEEDR &= ~(0x3u <<shiftBy);
  m_GPIO.m_registers->m_OSPEEDR |= static_cast<uint32_t>(ospeed) <<shiftBy;

  return *this;
}

GPIO::OuPin volatile& GPIO::OuPin::set() volatile
{
  m_GPIO.m_registers->m_BSRR |= static_cast<uint16_t>(0x1) <<m_nPin;

  return *this;
}

GPIO::OuPin volatile& GPIO::OuPin::reset() volatile
{
  m_GPIO.m_registers->m_BSRR |= static_cast<uint16_t>(0x1) <<(m_nPin + 16);

  return *this;
}

bool GPIO::OuPin::getOutputState() volatile
{
  return (m_GPIO.m_registers->m_ODR & (static_cast<uint16_t>(0x1) <<m_nPin));
}

bool GPIO::InPin::getInputState() volatile
{
  return (m_GPIO.m_registers->m_IDR & (static_cast<uint16_t>(0x1) <<m_nPin));
}

GPIO::AlPin volatile& GPIO::AlPin::setOutputSpeed(GPIO::AlPin::OutputSpeed const ospeed) volatile
{
  reinterpret_cast<GPIO::OuPin volatile&>(*this).setOutputSpeed(
        static_cast<typename GPIO::OuPin::OutputSpeed>(ospeed));

  return *this;
}

GPIO::AlPin volatile& GPIO::AlPin::setAF(GPIO::AlPin::AF const af) volatile
{
  const uint32_t offset{ m_nPin / 8u };
  const uint32_t shift{ (m_nPin * 4u) % 32u };
  m_GPIO.m_registers->m_AFR[offset] &= ~(0xFu <<shift);
  m_GPIO.m_registers->m_AFR[offset] |= static_cast<uint32_t const>(af) <<shift;

  return *this;
}

} //NS stm32f429
