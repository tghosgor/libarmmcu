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

#include <peripheral/GPIO.hpp>
#include <register/RCC.hpp>

#include <peripheral/SPI.hpp>

namespace stm32f429
{

const SPI::Module SPI::_1 { 0x40013000, std::make_pair(0x40023800 + 0x44, 0x1 <<12) };
const SPI::Module SPI::_5 { 0x40015000, std::make_pair(0x40023800 + 0x44, 0x1 <<20) };

void SPI::enable(DataFrame const dataFrameFormat, bool const enableHardwareCRC) volatile
{
  GPIO::Port portF(GPIO::Port::F);

  auto pin7 = portF.createPin(7, GPIO::Port::AlternatePin);
  auto pin8 = portF.createPin(8, GPIO::Port::AlternatePin);
  auto pin9 = portF.createPin(9, GPIO::Port::AlternatePin);

  pin7.setPullMode(GPIO::Port::AlPin::PullMode::PullDown);
  pin8.setPullMode(GPIO::Port::AlPin::PullMode::PullDown);
  pin9.setPullMode(GPIO::Port::AlPin::PullMode::PullDown);

  pin7.setOutputSpeed(GPIO::Port::AlPin::OutputSpeed::Medium);
  pin8.setOutputSpeed(GPIO::Port::AlPin::OutputSpeed::Medium);
  pin9.setOutputSpeed(GPIO::Port::AlPin::OutputSpeed::Medium);

  pin7.setAF(GPIO::Port::AlPin::AF::_5);
  pin8.setAF(GPIO::Port::AlPin::AF::_5);
  pin9.setAF(GPIO::Port::AlPin::AF::_5);

  m_CR1 |= static_cast<uint32_t const>(dataFrameFormat) <<11 | static_cast<uint32_t const>(enableHardwareCRC) <<13;
  m_CR1 |= 0x1u <<6;//TODO: üstteki satır ayarlanmadan SPI açmayın diyor ama bu şekil ayırmaya gerek var mı?
}

void SPI::setMasterMode() volatile
{
  m_CR1 |= 0x1u <<2;
}

void SPI::setSlaveMode() volatile
{
  m_CR1 &= ~(0x1u <<2);
}

void SPI::setBidirectionalMode() volatile
{
  m_CR1 |= 0x1u <<15;
}

void SPI::setUnidirectionalMode() volatile
{
  m_CR1 &= ~(0x1u <<15);
}

void SPI::setBaudPrescaler(BaudPSC const psc) volatile
{
  m_CR1 &= ~(0x7u <<3);
  m_CR1 |= static_cast<uint32_t const>(psc) <<3;
}

void SPI::enableSoftwareSlaveMode() volatile
{
  m_CR1 |= 0x1u <<9;
}

void SPI::disableSoftwareSlaveMode() volatile
{
  m_CR1 &= ~(0x1u <<9);
}

void SPI::enableInternalSlaveSelect() volatile
{
  m_CR1 |= 0x1u <<8;
}

void SPI::disableInternalSlaveSelect() volatile
{
  m_CR1 &= ~(0x1u <<8);
}

void SPI::send(uint16_t data) volatile
{
  m_DR = data;
  while(! (m_SR & (0x1u <<1))) //wait until txe is set to send data
  { }
  while(m_SR & (0x1u <<7)) //wait for tx bsy is reset
  { }
  if(! (m_CR1 & 0x1u <<15)) //2lines unidirectional mode
    m_SR &= ~(0x1u <<6); //clear OVR
}

SPI::DataFrame SPI::getDataFrameFormat() volatile const
{
  return static_cast<DataFrame>(m_CR1 & (0x1u <<11));
}

} //NS stm32f429
