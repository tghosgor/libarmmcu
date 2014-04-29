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

#ifndef LCD_H_
#define LCD_H_

#include <cstdint>

#include <RCC.h>

namespace stm32f429
{

class LCD
{
public:
  static constexpr std::size_t BaseAddress = 0x40016800;

public: //Declarations
  class Layer
  {
  public: //Registers
    uint32_t m_CR;
    uint32_t m_WHPCR;
    uint32_t m_WVPCR;
    uint32_t m_CKCR;
    uint32_t m_PFCR;
    uint32_t m_CACR;
    uint32_t m_DCCR;
    uint32_t m_BFCR;
    uint32_t PADDING6[2];
    uint32_t m_CFBAR;
    uint32_t m_CFBLR;
    uint32_t m_CFBLNR;
    uint32_t PADDING7[3];
    uint32_t m_CLUTWR;
  };

  enum : std::size_t
  {
    Layer1 = BaseAddress + (19 * 4),           //LCD::Periph<_0>::BaseAddress + sizeof(LCD::Periph<_0>)
    Layer2 = Layer1 + sizeof(Layer) + 15 * 4 //Layer1 + sizeof(Layer<Layer1>) + offset
  };

  static_assert(sizeof(Layer) == 17 * 4, "Layer size is wrong");

public: //Methods
  LCD();

  void enable() volatile;
  void setSync(uint16_t const hSync, uint16_t const vSync) volatile;
  void setBackPorch(uint16_t const hBP, uint16_t const vBP) volatile;
  void setActiveWidth(uint16_t const width, uint16_t const height) volatile;
  void setTotalWidth(uint16_t const width, uint16_t const height) volatile;
  void immediateReload() volatile;
  void blankingReload() volatile;
  void setBgColor(uint8_t const r, uint8_t const g, uint8_t const b) volatile;

  void writeData() { }

public: //Registers
  uint32_t PADDING1[2];
  uint32_t m_SSCR;
  uint32_t m_BPCR;
  uint32_t m_AWCR;
  uint32_t m_TWCR;
  uint32_t m_GCR;
  uint32_t PADDING2[2];
  uint32_t m_SRCR;
  uint32_t PADDING3[1];
  uint32_t m_BCCR;
  uint32_t PADDING4[1];
  uint32_t m_IER;
  uint32_t m_ISR;
  uint32_t m_ICR;
  uint32_t m_LIPCR;
  uint32_t m_CPSR;
  uint32_t m_CDSR;

  uint32_t PADDING5[14]; // 19 * 4 bytes until here

  Layer LAYER1;

  uint32_t PADDING8[15];

  Layer LAYER2;

private:
  GPIO::Port volatile* portD = RCC::enablePeriph<RCC::GPIOD>();
  GPIO::Port volatile* portC = RCC::enablePeriph<RCC::GPIOC>();

  GPIO::Port::OPin m_RDX = portD->createPin(12, GPIO::Port::OutputPin);
  GPIO::Port::OPin m_WRX = portD->createPin(13, GPIO::Port::OutputPin);
  GPIO::Port::OPin m_CSX = portC->createPin(2 , GPIO::Port::OutputPin);
}; //class LCD

static_assert(sizeof(LCD) == 0x148 + sizeof(GPIO::Port volatile*) * 2 + sizeof(GPIO::Port::OPin) * 3, "LCD size is not correct, spec says 0x148 bytes.");

} //NS stm32f429

#include "impl/LCD.impl"

#endif /* LCD_H_ */
