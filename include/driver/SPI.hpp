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

#ifndef SPI_H_
#define SPI_H_

#include "include/driver/fwd.hpp"
#include "include/driver/util.hpp"

#include <cstdint>

namespace stm32f429
{

class SPI
{
  friend class RCC;

public: //Declarations
  using Module = util::Module<1>;

  static Module _1;
  static Module _5;

  enum class DataFrame : bool
  {
    _8Bit = false,
    _16Bit = true
  };

  enum class BaudPSC : uint8_t
  {
    _0 = 0,
    _4 = 1,
    _8 = 2,
    _16 = 3,
    _32 = 4,
    _64 = 5,
    _128 = 6,
    _256 = 7
  };

public: //Methods
  SPI(const Module&);

  void enable(DataFrame const dataFrameFormat = DataFrame::_8Bit, bool const enableHardwareCRC = false) volatile;
  void setMasterMode() volatile;
  void setSlaveMode() volatile;
  void setBidirectionalMode() volatile;
  void setUnidirectionalMode() volatile;
  void setBaudPrescaler(BaudPSC const psc) volatile;
  void enableSoftwareSlaveMode() volatile;
  void disableSoftwareSlaveMode() volatile;
  void enableInternalSlaveSelect() volatile;
  void disableInternalSlaveSelect() volatile;
  void send(uint16_t data) volatile;

  DataFrame getDataFrameFormat() volatile const;

private:
  uint32_t m_CR1;
  uint32_t m_CR2;
  uint32_t m_SR;
  uint32_t m_DR;
  uint32_t m_CRCPR;
  uint32_t m_RXCRCR;
  uint32_t m_TXCRCR;
  uint32_t m_I2SCFGR;
  uint32_t m_I2SPR;

private:
  SPI() { }
};

} //NS stm32f429

#endif /* SPI_H_ */
