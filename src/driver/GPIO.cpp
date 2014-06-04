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

#include <driver/GPIO.hpp>

#include <driver/RCC.hpp>
#include <exception.hpp>

#include <type_traits>

namespace stm32f429
{
namespace GPIO
{

const Port::Module Port::A { 0x40020000, std::make_pair(0x40023800 + 0x30, 0x1 <<0) };
const Port::Module Port::B { 0x40020400, std::make_pair(0x40023800 + 0x30, 0x1 <<1) };
const Port::Module Port::C { 0x40020800, std::make_pair(0x40023800 + 0x30, 0x1 <<2) };
const Port::Module Port::D { 0x40020C00, std::make_pair(0x40023800 + 0x30, 0x1 <<3) };
const Port::Module Port::E { 0x40021000, std::make_pair(0x40023800 + 0x30, 0x1 <<4) };
const Port::Module Port::F { 0x40021400, std::make_pair(0x40023800 + 0x30, 0x1 <<5) };
const Port::Module Port::G { 0x40021800, std::make_pair(0x40023800 + 0x30, 0x1 <<6) };
const Port::Module Port::H { 0x40021C00, std::make_pair(0x40023800 + 0x30, 0x1 <<7) };
const Port::Module Port::I { 0x40022000, std::make_pair(0x40023800 + 0x30, 0x1 <<8) };

std::array<bool, 15> Port::Pin::m_isUsed;

Port::Port(const Module& module)
  : m_registers(reinterpret_cast<Registers* const>(module.m_moduleAddress))
{
  if(module.isEnabled())
    throw exception::Error("Port is already enabled.");
  module.enable();
}

template<class PinType_>
typename PinType_::type Port::createPin(uint8_t const nPin, PinType_ const) volatile
{
  return typename PinType_::type(nPin, *this);
}

template
decltype(Port::InputPin)::type Port::createPin(uint8_t const nPin, decltype(Port::InputPin) const) volatile;
template
decltype(Port::OutputPin)::type Port::createPin(uint8_t const nPin, decltype(Port::OutputPin) const) volatile;
template
decltype(Port::AlternatePin)::type Port::createPin(uint8_t const nPin, decltype(Port::AlternatePin) const) volatile;
template
decltype(Port::AnalogPin)::type Port::createPin(uint8_t const nPin, decltype(Port::AnalogPin) const) volatile;

Port::Pin::Pin(uint8_t const nPin, Port volatile& port)
  : m_nPin(nPin)
  , m_port(port)
{
  if(Pin::m_isUsed[nPin] == true)
    throw exception::Error("Pin already used.");
  Pin::m_isUsed[nPin] = true;
  const uint32_t shiftBy { (nPin * 2u) };
  m_port.m_registers->m_MODER &= ~(0x3u <<shiftBy);
}

Port::Pin::~Pin()
{
  Pin::m_isUsed[m_nPin] = false;
}

Port::InPin::InPin(uint8_t const nPin, Port volatile& port)
  : Pin(nPin, port)
{ }

Port::OuPin::OuPin(uint8_t const nPin, Port volatile& port)
  : Pin(nPin, port)
{
  const uint32_t shiftBy { (nPin * 2u) };
  m_port.m_registers->m_MODER |= static_cast<uint32_t>(0x1) <<shiftBy;
}

Port::AlPin::AlPin(uint8_t const nPin, Port volatile& port)
  : Pin(nPin, port)
{
  const uint32_t shiftBy { (nPin * 2u) };
  m_port.m_registers->m_MODER |= static_cast<uint32_t>(0x2) <<shiftBy;
}

Port::AnPin::AnPin(const uint8_t nPin, volatile Port& port)
: Pin(nPin, port)
{
  const uint32_t shiftBy { (nPin * 2u) };
  m_port.m_registers->m_MODER |= static_cast<uint32_t>(0x3) <<shiftBy;
}

void Port::Pin::setPullMode(typename Port::Pin::PullMode const ppm) volatile
{
  const uint32_t shiftBy { m_nPin * 2u };
  m_port.m_registers->m_PUPDR &= ~(0x3u <<shiftBy);
  m_port.m_registers->m_PUPDR |= static_cast<uint32_t>(ppm) <<shiftBy;
}

Port::OuPin volatile& Port::OuPin::setOutputSpeed(Port::OuPin::OutputSpeed const ospeed) volatile
{
  const uint32_t shiftBy { m_nPin * 2u };
  m_port.m_registers->m_OSPEEDR &= ~(0x3u <<shiftBy);
  m_port.m_registers->m_OSPEEDR |= static_cast<uint32_t>(ospeed) <<shiftBy;

  return *this;
}

Port::OuPin volatile& Port::OuPin::set() volatile
{
  m_port.m_registers->m_BSRR |= static_cast<uint16_t>(0x1u) <<m_nPin;

  return *this;
}

Port::OuPin volatile& Port::OuPin::reset() volatile
{
  m_port.m_registers->m_BSRR |= static_cast<uint16_t>(0x1u) <<(m_nPin + 16);

  return *this;
}

bool Port::InPin::getInputState() volatile
{
  return (m_port.m_registers->m_IDR & (static_cast<uint16_t>(0x1u) <<m_nPin));
}

bool Port::OuPin::getOutputState() volatile
{
  return (m_port.m_registers->m_ODR & (static_cast<uint16_t>(0x1u) <<m_nPin));
}

Port::AlPin volatile& Port::AlPin::setOutputSpeed(Port::AlPin::OutputSpeed const ospeed) volatile
{
  reinterpret_cast<Port::OuPin volatile&>(*this).setOutputSpeed(
        static_cast<typename Port::OuPin::OutputSpeed>(ospeed));

  return *this;
}

Port::AlPin volatile& Port::AlPin::setAF(Port::AlPin::AF const af) volatile
{
  const uint32_t offset{ m_nPin / 8u };
  const uint32_t shift{ (m_nPin * 4u) % 32u };
  m_port.m_registers->m_AFR[offset] &= ~(0xFu <<shift);
  m_port.m_registers->m_AFR[offset] |= static_cast<uint32_t const>(af) <<shift;

  return *this;
}

} //NS GPIO
} //NS stm32f429
