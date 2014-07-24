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

#include "include/driver/GPIO.hpp"
#include "include/driver/RCC.hpp"

#include "include/driver/SPI.hpp"

namespace stm32f429
{

SPI::Module SPI::_1(0x40013000, {{0x40023800 + 0x44, 0x1 <<12}});
SPI::Module SPI::_5(0x40015000, {{0x40023800 + 0x44, 0x1 <<20}});

SPI::SPI(const Module& module) {
  module.enable();
}

void SPI::enable(DataFrame const dataFrameFormat, bool const enableHardwareCRC) volatile
{
  GPIO portF(GPIO::F);

  auto pin7 = portF.createPin(7, GPIO::AlternatePin);
  auto pin8 = portF.createPin(8, GPIO::AlternatePin);
  auto pin9 = portF.createPin(9, GPIO::AlternatePin);

  pin7.setPullMode(GPIO::AlPin::PullMode::PullDown);
  pin8.setPullMode(GPIO::AlPin::PullMode::PullDown);
  pin9.setPullMode(GPIO::AlPin::PullMode::PullDown);

  pin7.setOutputSpeed(GPIO::AlPin::OutputSpeed::Medium);
  pin8.setOutputSpeed(GPIO::AlPin::OutputSpeed::Medium);
  pin9.setOutputSpeed(GPIO::AlPin::OutputSpeed::Medium);

  pin7.setAF(GPIO::AlPin::AF::_5);
  pin8.setAF(GPIO::AlPin::AF::_5);
  pin9.setAF(GPIO::AlPin::AF::_5);

  m_CR1 |= static_cast<uint32_t const>(dataFrameFormat) <<11 | static_cast<uint32_t const>(enableHardwareCRC) <<13;
  m_CR1 |= 0x1 <<6;//TODO: üstteki satır ayarlanmadan SPI açmayın diyor ama bu şekil ayırmaya gerek var mı?
}

void SPI::setMasterMode() volatile
{
  m_CR1 |= 0x1 <<2;
}

void SPI::setSlaveMode() volatile
{
  m_CR1 &= ~(0x1 <<2);
}

void SPI::setBidirectionalMode() volatile
{
  m_CR1 |= 0x1 <<15;
}

void SPI::setUnidirectionalMode() volatile
{
  m_CR1 &= ~(0x1 <<15);
}

void SPI::setBaudPrescaler(BaudPSC const psc) volatile
{
  m_CR1 &= ~(0x7u <<3);
  m_CR1 |= static_cast<uint32_t const>(psc) <<3;
}

void SPI::enableSoftwareSlaveMode() volatile
{
  m_CR1 |= 0x1 <<9;
}

void SPI::disableSoftwareSlaveMode() volatile
{
  m_CR1 &= ~(0x1 <<9);
}

void SPI::enableInternalSlaveSelect() volatile
{
  m_CR1 |= 0x1 <<8;
}

void SPI::disableInternalSlaveSelect() volatile
{
  m_CR1 &= ~(0x1 <<8);
}

void SPI::send(uint16_t data) volatile
{
  m_DR = data;
  while(! (m_SR & (0x1 <<1))) //wait until txe is set to send data
  { }
  while(m_SR & (0x1 <<7)) //wait for tx bsy is reset
  { }
  if(! (m_CR1 & 0x1 <<15)) //2lines unidirectional mode
    m_SR &= ~(0x1 <<6); //clear OVR
}

SPI::DataFrame SPI::getDataFrameFormat() volatile const
{
  return static_cast<DataFrame>(m_CR1 & (0x1 <<11));
}

} //NS stm32f429
