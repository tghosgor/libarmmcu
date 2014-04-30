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

#ifndef SPI_H_
#define SPI_H_

#include <cstdint>

#include <fwd.h>
#include <util.h>

namespace stm32f429
{

class SPI
{
  friend RCC;

public: //Declarations
  enum : uint32_t
  {
    _1 = 0x40013000,
    _5 = 0x40015000
  };

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
  void enable(DataFrame const dataFrameFormat = DataFrame::_8Bit, bool const enableHardwareCRC = false) volatile;
  void setMasterMode() volatile;
  void setSlaveMode() volatile;
  void setBidirectionalMode() volatile;
  void setUnidirectionalMode() volatile;
  void setBaudPrescaler(BaudPSC const psc) volatile;
  void enableSoftwareSlaveMode() volatile;
  void disableSoftwareSlaveMode() volatile;
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

#include <impl/SPI.impl>

#endif /* SPI_H_ */
