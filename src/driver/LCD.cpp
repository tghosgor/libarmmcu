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

#ifndef LCD_CPP_
#define LCD_CPP_

#include <driver/LCD.h>

#include <driver/SPI.h>
#include <window/desktop.h>
#include <window/text_window.h>


//#include <st_logo1.h>
//#include <fonts/basic.h>
//#include <img/smiley.h>

namespace stm32f429
{

GPIO::Port::OPin LCD::m_RDX = RCC::enablePeriph<RCC::GPIOD>()->createPin(12, GPIO::Port::OutputPin);
GPIO::Port::OPin LCD::m_WRX = RCC::enablePeriph<RCC::GPIOD>()->createPin(13, GPIO::Port::OutputPin);
GPIO::Port::OPin LCD::m_CSX = RCC::enablePeriph<RCC::GPIOC>()->createPin(2 , GPIO::Port::OutputPin);

SPI volatile* LCD::m_spi5 = RCC::enablePeriph<RCC::SPI5>();

LCD::Color::Color(uint8_t const red, uint8_t const green, uint8_t const blue)
  : m_color(static_cast<uint32_t>(red) <<16 | static_cast<uint32_t>(green) <<8 | static_cast<uint32_t>(blue) <<0)
{ }

LCD::LCD()
{ }

void LCD::enable(
    uint16_t const activeWidth, uint16_t const hSync, uint16_t const hBackPorch, uint16_t const HFP,
    uint16_t const activeHeight, uint16_t const vSync, uint16_t const vBackPorch, uint16_t const VFP) volatile
{
  RCC::instance()->m_CR &= ~(0x1 <<24); //PLLON OFF
  while (RCC::instance()->m_CR & (0x1 <<25))
  { }
  RCC::instance()->m_PLLCFGR &= ~(0x3F <<0 | 0x1FF <<6 | 0x3 <<16 | 0xF <<24);
  RCC::instance()->m_PLLCFGR |= 8 <<0; //PLL division PLLM
  RCC::instance()->m_PLLCFGR |= 360 <<6; //PLL multiplication PLLN
  RCC::instance()->m_PLLCFGR |= 0x0 <<16; //PLL division for main system clock PLLP
  RCC::instance()->m_PLLCFGR |=  7 <<24; //PLL main division for usb otg fs, sdio, rng PLLQ
  RCC::instance()->m_PLLCFGR |= 0x1 <<22; //PLL source is HSE

  RCC::instance()->m_CR |= 0x1 <<16; //HSEON
  while (! RCC::instance()->m_CR & (0x1 <<17))
  { }
  RCC::instance()->m_CR |= 0x1 <<24; //PLLON
  while (!RCC::instance()->m_CR & (0x1 <<25))
  { }

  //*reinterpret_cast<uint8_t* const>(0x40023C00) = 5; //FLASH Latency 5
  //RCC::instance()->m_CFGR |= 0x2 <<0; //PLL as SYSCLK
  //RCC::instance()->m_CFGR |= 0x0 <<4; //AHB PSC 1
  //RCC::instance()->m_CFGR |= 0x5 <<10; //APB1 PSC 4
  //RCC::instance()->m_CFGR |= 0x4 <<13; //APB2 PSC 2

  RCC::instance()->disablePLLSAI();
  while(RCC::instance()->isPLLSAILocked())
  { }
  RCC::instance()->enablePLLSAI(4, 4, 192, RCC::PLLSAIDiv::_8);
  while(!RCC::instance()->isPLLSAILocked())
  { }

  m_RDX.setOutputSpeed(GPIO::Port::OPin::OutputSpeed::Fast);
  m_WRX.setOutputSpeed(GPIO::Port::OPin::OutputSpeed::Fast);
  m_CSX.setOutputSpeed(GPIO::Port::OPin::OutputSpeed::Fast);

  auto portA = RCC::enablePeriph<RCC::GPIOA>();
  auto portB = RCC::enablePeriph<RCC::GPIOB>();
  auto portC = RCC::enablePeriph<RCC::GPIOC>();
  auto portD = RCC::enablePeriph<RCC::GPIOD>();
  auto portF = RCC::enablePeriph<RCC::GPIOF>();
  auto portG = RCC::enablePeriph<RCC::GPIOG>();

  /*
   +------------------------+-----------------------+----------------------------+
   +                       LCD pins assignment                                   +
   +------------------------+-----------------------+----------------------------+
   |  LCD_TFT R2 <-> PC.10  |  LCD_TFT G2 <-> PA.06 |  LCD_TFT B2 <-> PD.06      |
   |  LCD_TFT R3 <-> PB.00  |  LCD_TFT G3 <-> PG.10 |  LCD_TFT B3 <-> PG.11      |
   |  LCD_TFT R4 <-> PA.11  |  LCD_TFT G4 <-> PB.10 |  LCD_TFT B4 <-> PG.12      |
   |  LCD_TFT R5 <-> PA.12  |  LCD_TFT G5 <-> PB.11 |  LCD_TFT B5 <-> PA.03      |
   |  LCD_TFT R6 <-> PB.01  |  LCD_TFT G6 <-> PC.07 |  LCD_TFT B6 <-> PB.08      |
   |  LCD_TFT R7 <-> PG.06  |  LCD_TFT G7 <-> PD.03 |  LCD_TFT B7 <-> PB.09      |
   -------------------------------------------------------------------------------
            |  LCD_TFT HSYNC <-> PC.06  | LCDTFT VSYNC <->  PA.04 |
            |  LCD_TFT CLK   <-> PG.07  | LCD_TFT DE   <->  PF.10 |
             -----------------------------------------------------

  */

  portC->createPin(6, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_14)
      .setOutputSpeed(GPIO::Port::APin::OutputSpeed::Fast).setPullMode(GPIO::Port::APin::PullMode::None);//HSYNC
  portA->createPin(4, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_14)
      .setOutputSpeed(GPIO::Port::APin::OutputSpeed::Fast).setPullMode(GPIO::Port::APin::PullMode::None);//VSYNC
  portG->createPin(7, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_14)
      .setOutputSpeed(GPIO::Port::APin::OutputSpeed::Fast).setPullMode(GPIO::Port::APin::PullMode::None);//CLK
  portF->createPin(10, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_14)
      .setOutputSpeed(GPIO::Port::APin::OutputSpeed::Fast).setPullMode(GPIO::Port::APin::PullMode::None);//DE

  portC->createPin(10, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_14)
      .setOutputSpeed(GPIO::Port::APin::OutputSpeed::Fast).setPullMode(GPIO::Port::APin::PullMode::None);//R2
  portB->createPin(0, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_14)
      .setOutputSpeed(GPIO::Port::APin::OutputSpeed::Fast).setPullMode(GPIO::Port::APin::PullMode::None);//R3
  portA->createPin(11, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_14)
      .setOutputSpeed(GPIO::Port::APin::OutputSpeed::Fast).setPullMode(GPIO::Port::APin::PullMode::None);//R4
  portA->createPin(12, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_14)
      .setOutputSpeed(GPIO::Port::APin::OutputSpeed::Fast).setPullMode(GPIO::Port::APin::PullMode::None);//R5
  portB->createPin(1, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_14)
      .setOutputSpeed(GPIO::Port::APin::OutputSpeed::Fast).setPullMode(GPIO::Port::APin::PullMode::None);//R6
  portG->createPin(6, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_14)
      .setOutputSpeed(GPIO::Port::APin::OutputSpeed::Fast).setPullMode(GPIO::Port::APin::PullMode::None);//R7

  portA->createPin(6, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_14)
      .setOutputSpeed(GPIO::Port::APin::OutputSpeed::Fast).setPullMode(GPIO::Port::APin::PullMode::None);//G2
  portG->createPin(10, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_14)
      .setOutputSpeed(GPIO::Port::APin::OutputSpeed::Fast).setPullMode(GPIO::Port::APin::PullMode::None);//G3
  portB->createPin(10, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_14)
      .setOutputSpeed(GPIO::Port::APin::OutputSpeed::Fast).setPullMode(GPIO::Port::APin::PullMode::None);//G4
  portB->createPin(11, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_14)
      .setOutputSpeed(GPIO::Port::APin::OutputSpeed::Fast).setPullMode(GPIO::Port::APin::PullMode::None);//G5
  portC->createPin(7, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_14)
      .setOutputSpeed(GPIO::Port::APin::OutputSpeed::Fast).setPullMode(GPIO::Port::APin::PullMode::None);//G6
  portD->createPin(3, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_14)
      .setOutputSpeed(GPIO::Port::APin::OutputSpeed::Fast).setPullMode(GPIO::Port::APin::PullMode::None);//G7

  portD->createPin(6, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_14)
      .setOutputSpeed(GPIO::Port::APin::OutputSpeed::Fast).setPullMode(GPIO::Port::APin::PullMode::None);//B2
  portG->createPin(11, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_14)
      .setOutputSpeed(GPIO::Port::APin::OutputSpeed::Fast).setPullMode(GPIO::Port::APin::PullMode::None);//B3
  portG->createPin(12, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_14)
      .setOutputSpeed(GPIO::Port::APin::OutputSpeed::Fast).setPullMode(GPIO::Port::APin::PullMode::None);//B4
  portA->createPin(3, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_14)
      .setOutputSpeed(GPIO::Port::APin::OutputSpeed::Fast).setPullMode(GPIO::Port::APin::PullMode::None);//B5
  portB->createPin(8, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_14)
      .setOutputSpeed(GPIO::Port::APin::OutputSpeed::Fast).setPullMode(GPIO::Port::APin::PullMode::None);//B6
  portB->createPin(9, GPIO::Port::AlternatePin).setAF(GPIO::Port::APin::AF::_14)
      .setOutputSpeed(GPIO::Port::APin::OutputSpeed::Fast).setPullMode(GPIO::Port::APin::PullMode::None);//B7

  /* Set or Reset the control line */
  m_CSX.reset();
  m_CSX.set();

  m_spi5->enable(SPI::DataFrame::_8Bit);
  m_spi5->setBaudPrescaler(SPI::BaudPSC::_16);
  m_spi5->setUnidirectionalMode();
  m_spi5->enableSoftwareSlaveMode();
  m_spi5->enableInternalSlaveSelect();
  m_spi5->setMasterMode();

  /*Configure LCD*/
  selectReg(0xCA);
  writeReg(0xC3);
  writeReg(0x08);
  writeReg(0x50);
  selectReg(LCD_POWERB);
  writeReg(0x00);
  writeReg(0xC1);
  writeReg(0x30);
  selectReg(LCD_POWER_SEQ);
  writeReg(0x64);
  writeReg(0x03);
  writeReg(0x12);
  writeReg(0x81);
  selectReg(LCD_DTCA);
  writeReg(0x85);
  writeReg(0x00);
  writeReg(0x78);
  selectReg(LCD_POWERA);
  writeReg(0x39);
  writeReg(0x2C);
  writeReg(0x00);
  writeReg(0x34);
  writeReg(0x02);
  selectReg(LCD_PRC);
  writeReg(0x20);
  selectReg(LCD_DTCB);
  writeReg(0x00);
  writeReg(0x00);
  selectReg(LCD_FRMCTR1);
  writeReg(0x00);
  writeReg(0x1B);
  selectReg(LCD_DFC);
  writeReg(0x0A);
  writeReg(0xA2);
  selectReg(LCD_POWER1);
  writeReg(0x10);
  selectReg(LCD_POWER2);
  writeReg(0x10);
  selectReg(LCD_VCOM1);
  writeReg(0x45);
  writeReg(0x15);
  selectReg(LCD_VCOM2);
  writeReg(0x90);
  selectReg(LCD_MAC);
  writeReg(0xC8);
  selectReg(LCD_3GAMMA_EN);
  writeReg(0x00);
  selectReg(LCD_RGB_INTERFACE);
  writeReg(0xC2);
  selectReg(LCD_DFC);
  writeReg(0x0A);
  writeReg(0xA7);
  writeReg(0x27);
  writeReg(0x04);

  /* colomn address set */
  selectReg(LCD_COLUMN_ADDR);
  writeReg(0x00);
  writeReg(0x00);
  writeReg(0x00);
  writeReg(0xEF);
  /* Page Address Set */
  selectReg(LCD_PAGE_ADDR);
  writeReg(0x00);
  writeReg(0x00);
  writeReg(0x01);
  writeReg(0x3F);
  selectReg(LCD_INTERFACE);
  writeReg(0x01);
  writeReg(0x00);
  writeReg(0x06);

  selectReg(LCD_GRAM);
  //LCD_Delay(200);
  uint32_t volatile i = 0;
  while(++i < 999999); //temporary enough?

  selectReg(LCD_GAMMA);
  writeReg(0x01);

  selectReg(LCD_PGAMMA);
  writeReg(0x0F);
  writeReg(0x29);
  writeReg(0x24);
  writeReg(0x0C);
  writeReg(0x0E);
  writeReg(0x09);
  writeReg(0x4E);
  writeReg(0x78);
  writeReg(0x3C);
  writeReg(0x09);
  writeReg(0x13);
  writeReg(0x05);
  writeReg(0x17);
  writeReg(0x11);
  writeReg(0x00);
  selectReg(LCD_NGAMMA);
  writeReg(0x00);
  writeReg(0x16);
  writeReg(0x1B);
  writeReg(0x04);
  writeReg(0x11);
  writeReg(0x07);
  writeReg(0x31);
  writeReg(0x33);
  writeReg(0x42);
  writeReg(0x05);
  writeReg(0x0C);
  writeReg(0x0A);
  writeReg(0x28);
  writeReg(0x2F);
  writeReg(0x0F);

  selectReg(LCD_SLEEP_OUT);
  //LCD_Delay(200);
  i = 0;
  while(++i < 999999); //temporary enough?

  selectReg(LCD_DISPLAY_ON);
  /* GRAM start writing */
  selectReg(LCD_GRAM);

  setSync(hSync, vSync);;
  setBackPorch(hSync + hBackPorch, vSync + vBackPorch);
  setActiveWidth(activeWidth + hSync + hBackPorch, activeHeight + vSync + vBackPorch);
  setTotalWidth(activeWidth + hSync + hBackPorch + HFP, activeHeight + vSync + vBackPorch + VFP);

  m_GCR |= 0x1 <<0;

  /*uint32_t const imageWidth = smiley.width;
  uint32_t const imageHeight = smiley.height;
  uint32_t volatile const fbData = reinterpret_cast<uint32_t const volatile>(smiley.pixel_data);
  uint8_t const bytesPerPixel = smiley.bytes_per_pixel;*/

  extern uint8_t*  FrameBuffer;

  uint32_t const windowWidth = 240;
  uint32_t const windowHeight = 300;
  uint32_t volatile const fbData = reinterpret_cast<uint32_t const volatile>(&FrameBuffer);
  uint8_t const bytesPerPixel = 2;

  m_layer1.m_WHPCR &= ~(0xF000F000);
  m_layer1.m_WHPCR |= ((0 + ((m_BPCR & 0x0FFF0000) >> 16) + 1) | ((windowWidth + ((m_BPCR & 0x0FFF0000) >> 16)) << 16));
  m_layer1.m_WVPCR &= ~(0xF800F800);
  m_layer1.m_WVPCR |= ((0 + (m_BPCR & 0x000007FF) + 1) | ((windowHeight + (m_BPCR & 0x000007FF)) << 16));
  //m_layer1.m_WHPCR = 240 <<16;
  //m_layer1.m_WVPCR = 160 <<16;

  m_layer1.m_PFCR |= 0x2; //LTDC_PIXEL_FORMAT_RGB565+
  m_layer1.m_DCCR = 0;//default color
  m_layer1.m_CACR |= 255;
  m_layer1.m_BFCR |= 0x6 <<6 | 0x7; //LTDC_BLENDING_FACTOR2_PAxCA
  //m_layer1.m_CFBAR = reinterpret_cast<uint32_t>(&ST_LOGO_1);
  m_layer1.m_CFBAR = fbData;
  m_layer1.m_CFBLR &= ~(0xE000E000);
  m_layer1.m_CFBLR |= ((windowWidth * bytesPerPixel) <<16) | (windowWidth * bytesPerPixel + 3); //pitch increment from one line of pixels to another <<16 | Active high width x number of bytes per pixel + 3
  m_layer1.m_CFBLNR &= ~(0x3FF);
  m_layer1.m_CFBLNR |= windowHeight;
  m_layer1.m_CR |= 0x1;

  Desktop desktop;
  TextWindow textWindow(desktop);
  textWindow << "asd";

  immediateReload();
}

void LCD::setSync(uint16_t const hSync, uint16_t const vSync) volatile
{
  m_SSCR &= ~(0x0FFF <<16 | 0x07FF);
  m_SSCR |= (hSync - 1) <<16 | (vSync - 1);
}

void LCD::setBackPorch(uint16_t const hBP, uint16_t vBP) volatile
{
  m_BPCR &= ~(0x0FFF <<16 | 0x07FF);
  m_BPCR |= (hBP - 1) <<16 | (vBP - 1);
}

void LCD::setActiveWidth(uint16_t const width, uint16_t height) volatile
{
  m_AWCR &= ~(0x0FFF <<16 | 0x07FF);
  m_AWCR |= (width - 1) <<16 | (height - 1);
}

void LCD::setTotalWidth(uint16_t const width, uint16_t height) volatile
{
  m_TWCR &= ~(0x0FFF <<16 | 0x07FF);
  m_TWCR |= (width - 1) <<16 | (height - 1);
}

void LCD::immediateReload() volatile
{
  m_SRCR |= 0x1 <<0;
}

void LCD::blankingReload() volatile
{
  m_SRCR |= 0x1 <<1;
}

LCD::Color const volatile& LCD::getBgColor() volatile
{
  return reinterpret_cast<Color const volatile&>(m_BCCR);
}

void LCD::setBgColor(Color const color) volatile
{
  m_BCCR &= 0xFF000000;
  m_BCCR |= *reinterpret_cast<uint32_t const* const>(&color);
}

void LCD::enableInterrupt(Interrupt const interrupt) volatile
{
  m_IER |= static_cast<uint32_t>(interrupt);
}

void LCD::disableInterrupt(Interrupt const interrupt) volatile
{
  m_IER &= ~(static_cast<uint32_t>(interrupt));
}

void LCD::selectReg(uint8_t const reg) volatile
{
  //reset WRX to send command
  m_WRX.reset();
  //reset LCD control line - SPI select?
  m_CSX.reset();
  m_spi5->send(reg);
  //set LCD control line - SPI deselect?
  m_CSX.set();
}

void LCD::writeReg(uint8_t const value) volatile
{
  //set WRX to send data
  m_WRX.set();
  //reset LCD control line - SPI select?
  m_CSX.reset();
  m_spi5->send(value);
  //set LCD control line - SPI deselect?
  m_CSX.set();
}

bool operator==(LCD::Color volatile const& lhs, LCD::Color volatile const& rhs)
{
  return (reinterpret_cast<uint32_t volatile const&>(lhs) & 0x00FFFFFF) == (reinterpret_cast<uint32_t volatile const&>(rhs) & 0x00FFFFFF);
}

bool operator!=(LCD::Color volatile const& lhs, LCD::Color volatile const& rhs)
{
  return !operator==(lhs, rhs);
}

} //NS stm32f429

#endif /* LCD_CPP_ */
