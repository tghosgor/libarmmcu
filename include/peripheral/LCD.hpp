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

#include <peripheral/GPIO.hpp>
#include <register/RCC.hpp>

namespace stm32f429
{

class LCD
{
  friend class RCC;

public:
  static std::size_t constexpr BaseAddress = 0x40016800;

public: //Declarations
  struct Color
  {
  public:
    Color(uint8_t const red, uint8_t const green, uint8_t const blue);

  private:
    uint32_t m_color;
  };

  enum class Interrupt : uint32_t
  {
    Line = 0x1,
    FIFOUnderrun = 0x1 <<1,
    TransferError = 0x1 <<2,
    RegisterReload = 0x1 <<3
  };

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

  static_assert(sizeof(Layer) == 17 * 4, "Layer size is wrong");

public: //Methods
  LCD(GPIO::Port& portA, GPIO::Port& portB, GPIO::Port& portC, GPIO::Port& portD, GPIO::Port& portF, GPIO::Port& portG,
      const uint16_t activeWidth, const uint16_t hSync, const uint16_t hBackPorch, const uint16_t HFP, const uint16_t activeHeight,
      const uint16_t vSync, const uint16_t vBackPorch, const uint16_t VFP);
  //TODO: ~LCD();

  void setSync(uint16_t const hSync, uint16_t const vSync) volatile;
  void setBackPorch(uint16_t const hBP, uint16_t const vBP) volatile;
  void setActiveWidth(uint16_t const width, uint16_t const height) volatile;
  void setTotalWidth(uint16_t const width, uint16_t const height) volatile;
  void immediateReload() volatile;
  void blankingReload() volatile;
  Color volatile const& getBgColor() volatile;
  void setBgColor(Color const color) volatile;

  void enableInterrupt(Interrupt const interrupt) volatile;
  void disableInterrupt(Interrupt const interrupt) volatile;

  void selectReg(uint8_t offset) volatile;
  void writeReg(uint8_t value) volatile;

private:
  struct Registers
  {
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

    Layer m_layer1;

    uint32_t PADDING8[15];

    Layer m_layer2;
  };
  static_assert(sizeof(Registers) == 0x148, "LCD size is not correct, spec says 0x148 bytes.");

public: //Registers
  Registers* m_registers;

private: //TODO: this structure is placed on top of LCD-TFT register so the ones below has to be static
         // but there may be more than one LCD connected with different ports so this class should have a pointer
         // to the register along with a seperate "struct LCDRegister"
  static GPIO::Port::OuPin m_RDX;
  static GPIO::Port::OuPin m_WRX;
  static GPIO::Port::OuPin m_CSX;

  static SPI volatile* m_spi5;

private:
}; //class LCD

bool operator==(LCD::Color volatile const& lhs, LCD::Color volatile const& rhs);
bool operator!=(LCD::Color volatile const& lhs, LCD::Color volatile const& rhs);

} //NS stm32f429


/* Timing configuration  (Typical configuration from ILI9341 datasheet)
  HSYNC=10 (9+1)
  HBP=20 (29-10+1)
  ActiveW=240 (269-20-10+1)
  HFP=10 (279-240-20-10+1)

  VSYNC=2 (1+1)
  VBP=2 (3-2+1)
  ActiveH=320 (323-2-2+1)
  VFP=4 (327-320-2-2+1)
*/
#define  ILI9341_HSYNC            ((uint32_t)9)   /* Horizontal synchronization */
#define  ILI9341_HBP              ((uint32_t)29)    /* Horizontal back porch      */
#define  ILI9341_HFP              ((uint32_t)2)    /* Horizontal front porch     */
#define  ILI9341_VSYNC            ((uint32_t)1)   /* Vertical synchronization   */
#define  ILI9341_VBP              ((uint32_t)3)    /* Vertical back porch        */
#define  ILI9341_VFP              ((uint32_t)2)    /* Vertical front porch       */


/**
  * @brief  ILI9341 Registers
  */

/* Level 1 Commands */
#define LCD_SWRESET             0x01   /* Software Reset */
#define LCD_READ_DISPLAY_ID     0x04   /* Read display identification information */
#define LCD_RDDST               0x09   /* Read Display Status */
#define LCD_RDDPM               0x0A   /* Read Display Power Mode */
#define LCD_RDDMADCTL           0x0B   /* Read Display MADCTL */
#define LCD_RDDCOLMOD           0x0C   /* Read Display Pixel Format */
#define LCD_RDDIM               0x0D   /* Read Display Image Format */
#define LCD_RDDSM               0x0E   /* Read Display Signal Mode */
#define LCD_RDDSDR              0x0F   /* Read Display Self-Diagnostic Result */
#define LCD_SPLIN               0x10   /* Enter Sleep Mode */
#define LCD_SLEEP_OUT           0x11   /* Sleep out register */
#define LCD_PTLON               0x12   /* Partial Mode ON */
#define LCD_NORMAL_MODE_ON      0x13   /* Normal Display Mode ON */
#define LCD_DINVOFF             0x20   /* Display Inversion OFF */
#define LCD_DINVON              0x21   /* Display Inversion ON */
#define LCD_GAMMA               0x26   /* Gamma register */
#define LCD_DISPLAY_OFF         0x28   /* Display off register */
#define LCD_DISPLAY_ON          0x29   /* Display on register */
#define LCD_COLUMN_ADDR         0x2A   /* Colomn address register */
#define LCD_PAGE_ADDR           0x2B   /* Page address register */
#define LCD_GRAM                0x2C   /* GRAM register */
#define LCD_RGBSET              0x2D   /* Color SET */
#define LCD_RAMRD               0x2E   /* Memory Read */
#define LCD_PLTAR               0x30   /* Partial Area */
#define LCD_VSCRDEF             0x33   /* Vertical Scrolling Definition */
#define LCD_TEOFF               0x34   /* Tearing Effect Line OFF */
#define LCD_TEON                0x35   /* Tearing Effect Line ON */
#define LCD_MAC                 0x36   /* Memory Access Control register*/
#define LCD_VSCRSADD            0x37   /* Vertical Scrolling Start Address */
#define LCD_IDMOFF              0x38   /* Idle Mode OFF */
#define LCD_IDMON               0x39   /* Idle Mode ON */
#define LCD_PIXEL_FORMAT        0x3A   /* Pixel Format register */
#define LCD_WRITE_MEM_CONTINUE  0x3C   /* Write Memory Continue */
#define LCD_READ_MEM_CONTINUE   0x3E   /* Read Memory Continue */
#define LCD_SET_TEAR_SCANLINE   0x44   /* Set Tear Scanline */
#define LCD_GET_SCANLINE        0x45   /* Get Scanline */
#define LCD_WDB                 0x51   /* Write Brightness Display register */
#define LCD_RDDISBV             0x52   /* Read Display Brightness */
#define LCD_WCD                 0x53   /* Write Control Display register*/
#define LCD_RDCTRLD             0x54   /* Read CTRL Display */
#define LCD_WRCABC              0x55   /* Write Content Adaptive Brightness Control */
#define LCD_RDCABC              0x56   /* Read Content Adaptive Brightness Control */
#define LCD_WRITE_CABC          0x5E   /* Write CABC Minimum Brightness */
#define LCD_READ_CABC           0x5F   /* Read CABC Minimum Brightness */
#define LCD_READ_ID1            0xDA   /* Read ID1 */
#define LCD_READ_ID2            0xDB   /* Read ID2 */
#define LCD_READ_ID3            0xDC   /* Read ID3 */


/* Level 2 Commands */
#define LCD_RGB_INTERFACE       0xB0   /* RGB Interface Signal Control */
#define LCD_FRMCTR1             0xB1   /* Frame Rate Control (In Normal Mode) */
#define LCD_FRMCTR2             0xB2   /* Frame Rate Control (In Idle Mode) */
#define LCD_FRMCTR3             0xB3   /* Frame Rate Control (In Partial Mode) */
#define LCD_INVTR               0xB4   /* Display Inversion Control */
#define LCD_BPC                 0xB5   /* Blanking Porch Control register*/
#define LCD_DFC                 0xB6   /* Display Function Control register*/
#define LCD_ETMOD               0xB7   /* Entry Mode Set */
#define LCD_BACKLIGHT1          0xB8   /* Backlight Control 1 */
#define LCD_BACKLIGHT2          0xB9   /* Backlight Control 2 */
#define LCD_BACKLIGHT3          0xBA   /* Backlight Control 3 */
#define LCD_BACKLIGHT4          0xBB   /* Backlight Control 4 */
#define LCD_BACKLIGHT5          0xBC   /* Backlight Control 5 */
#define LCD_BACKLIGHT7          0xBE   /* Backlight Control 7 */
#define LCD_BACKLIGHT8          0xBF   /* Backlight Control 8 */
#define LCD_POWER1              0xC0   /* Power Control 1 register */
#define LCD_POWER2              0xC1   /* Power Control 2 register */
#define LCD_VCOM1               0xC5   /* VCOM Control 1 register */
#define LCD_VCOM2               0xC7   /* VCOM Control 2 register */
#define LCD_NVMWR               0xD0   /* NV Memory Write */
#define LCD_NVMPKEY             0xD1   /* NV Memory Protection Key */
#define LCD_RDNVM               0xD2   /* NV Memory Status Read */
#define LCD_READ_ID4            0xD3   /* Read ID4 */
#define LCD_PGAMMA              0xE0   /* Positive Gamma Correction register*/
#define LCD_NGAMMA              0xE1   /* Negative Gamma Correction register*/
#define LCD_DGAMCTRL1           0xE2   /* Digital Gamma Control 1 */
#define LCD_DGAMCTRL2           0xE3   /* Digital Gamma Control 2 */
#define LCD_INTERFACE           0xF6   /* Interface control register */

/* Extend register commands */
#define LCD_POWERA               0xCB   /* Power control A register */
#define LCD_POWERB               0xCF   /* Power control B register */
#define LCD_DTCA                 0xE8   /* Driver timing control A */
#define LCD_DTCB                 0xEA   /* Driver timing control B */
#define LCD_POWER_SEQ            0xED   /* Power on sequence register */
#define LCD_3GAMMA_EN            0xF2   /* 3 Gamma enable register */
#define LCD_PRC                  0xF7   /* Pump ratio control register */

/* Size of read registers*/
#define LCD_READ_ID4_SIZE        3      /* Size of Read ID4 */

#endif /* LCD_H_ */
