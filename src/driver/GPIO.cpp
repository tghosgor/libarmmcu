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

#include <driver/RCC.h>

#include <driver/GPIO.h>

#include <type_traits>

namespace stm32f429
{
namespace GPIO
{

template<class PinType_>
typename PinType_::type Port::createPin(uint8_t const nPin, PinType_ const) volatile
{
  const uint32_t shiftBy { (nPin * 2u) };
  m_MODER &= ~(0x3u <<shiftBy);
  m_MODER |= static_cast<uint32_t>(PinType_::moder) <<shiftBy;

  return typename PinType_::type(nPin, *this);
}

template
decltype(Port::InputPin)::type Port::createPin(uint8_t const nPin, decltype(Port::InputPin) const) volatile;
template
decltype(Port::OutputPin)::type Port::createPin(uint8_t const nPin, decltype(Port::OutputPin) const) volatile;
template
decltype(Port::AlternatePin)::type Port::createPin(uint8_t const nPin, decltype(Port::AlternatePin) const) volatile;

Port::Pin::Pin(uint8_t const nPin, Port volatile& port)
  : m_nPin(nPin)
  , m_port(port)
{ }

Port::OPin::OPin(uint8_t const nPin, Port volatile& port)
  : Pin(nPin, port)
{ }

Port::IPin::IPin(uint8_t const nPin, Port volatile& port)
  : Pin(nPin, port)
{ }

Port::APin::APin(uint8_t const nPin, Port volatile& port)
  : Pin(nPin, port)
{ }

void Port::Pin::setPullMode(typename Port::Pin::PullMode const ppm) volatile
{
  const uint32_t shiftBy { m_nPin * 2u };
  m_port.m_PUPDR &= ~(0x3u <<shiftBy);
  m_port.m_PUPDR |= static_cast<uint32_t>(ppm) <<shiftBy;
}

Port::OPin volatile& Port::OPin::setOutputSpeed(Port::OPin::OutputSpeed const ospeed) volatile
{
  const uint32_t shiftBy { m_nPin * 2u };
  m_port.m_OSPEEDR &= ~(0x3u <<shiftBy);
  m_port.m_OSPEEDR |= static_cast<uint32_t>(ospeed) <<shiftBy;

  return *this;
}

Port::OPin volatile& Port::OPin::set() volatile
{
  m_port.m_BSRR |= static_cast<uint16_t>(0x1u) <<m_nPin;

  return *this;
}

Port::OPin volatile& Port::OPin::reset() volatile
{
  m_port.m_BSRR |= static_cast<uint16_t>(0x1u) <<(m_nPin + 16);

  return *this;
}

bool Port::OPin::getOutputState() volatile
{
  return (m_port.m_ODR & (static_cast<uint16_t>(0x1u) <<m_nPin));
}

bool Port::IPin::getInputState() volatile
{
  return (m_port.m_IDR & (static_cast<uint16_t>(0x1u) <<m_nPin));
}

Port::APin volatile& Port::APin::setOutputSpeed(Port::APin::OutputSpeed const ospeed) volatile
{
  reinterpret_cast<Port::OPin volatile&>(*this).setOutputSpeed(
        static_cast<typename Port::OPin::OutputSpeed>(ospeed));

  return *this;
}

Port::APin volatile& Port::APin::setAF(Port::APin::AF const af) volatile
{
  const uint32_t offset{ m_nPin / 8u };
  const uint32_t shift{ (m_nPin * 4u) % 32u };
  m_port.m_AFR[offset] &= ~(0xFu <<shift);
  m_port.m_AFR[offset] |= static_cast<uint32_t const>(af) <<shift;

  return *this;
}

} //NS GPIO
} //NS stm32f429
