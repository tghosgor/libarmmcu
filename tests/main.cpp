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

#include <driver/ADC.hpp>
#include <driver/EXTI.hpp>
#include <driver/I2C.hpp>
#include <driver/IVTable.hpp>
#include <driver/GPIO.hpp>
#include <driver/LCD.hpp>
#include <driver/NVIC.hpp>
#include <driver/RCC.hpp>
#include <driver/RTC.hpp>
#include <driver/SCB.hpp>
#include <driver/SYSCFG.hpp>
#include <driver/TIM.hpp>

#include <window/compositor.hpp>
#include <window/text_window.hpp>
#include <font/arial_normal.hpp>
#include <font/arial_bold.hpp>

#include <cstring>
#include <cstdint>
#include <cstdio>
#include <limits>

namespace stm32f429
{
extern uint8_t* layerFrameBuffer;
}

using namespace stm32f429;

bool exti0Handler();
bool exti3Handler();

/*auto portA = RCC::enablePeriph<RCC::GPIOA>();
auto portApin0 = portA->createPin(0, GPIO::Port::InputPin);

auto portD = RCC::enablePeriph<RCC::GPIOD>();
auto portDpin2 = portD->createPin(2, GPIO::Port::InputPin);*/

auto portG = RCC::enablePeriph<RCC::GPIOG>();
auto portGpin13 = portG->createPin(13, GPIO::Port::OutputPin);
/*auto portGpin14 = portG->createPin(14, GPIO::Port::OutputPin);

auto syscfg = RCC::enablePeriph<RCC::SYSCFG>();
auto exti0syscfg = syscfg->enable<SYSCFG::EXTI0>();
auto exti0 = exti0syscfg->setSource(SYSCFG::EXTISource::PA);

auto extis2yscfg = syscfg->enable<SYSCFG::EXTI2>();
auto exti2 = extis2yscfg->setSource(SYSCFG::EXTISource::PD);*/

int main()
{
  portGpin13.set();

SET_UP_LCD:
  constexpr unsigned ActiveWidth = 240;
  constexpr unsigned ActiveHeight = 320;

  constexpr unsigned hSync = 10;
  constexpr unsigned HBP = 20;
  constexpr unsigned HFP = 10;

  constexpr unsigned vSync = 2;
  constexpr unsigned VBP = 2;
  constexpr unsigned VFP = 4;

  auto lcd0 = RCC::enablePeriph<RCC::LTDC>();
  lcd0->enable(ActiveWidth, hSync, HBP, HFP, ActiveHeight, vSync, VBP, VFP);
  //lcd0->setBgColor({255, 0, 0});
  lcd0->setBgColor({255, 255, 255});

SET_UP_EXTI0:
  //Configure EXTI0 to PA0 Rising Edge
  /*portApin0.setPullMode(GPIO::Port::IPin::PullMode::PullDown);
  portDpin2.setPullMode(GPIO::Port::IPin::PullMode::PullDown);
  exti0->registerISR(&exti0Handler);
  exti0->clearPending();
  exti0->enableRisingTrigger();
  exti0->enableInterrupt();
  exti2->registerISR(&exti3Handler);
  exti2->clearPending();
  exti2->enableRisingTrigger();
  exti2->enableInterrupt();*/

//Temporary Test Loop
SET_UP_TIM:
  auto TIM1 = RCC::enablePeriph<RCC::TIM1>();
  TIM1->setAutoReloadValue(std::numeric_limits<uint16_t>::max());
  TIM1->setPrescalerValue(1000);
  TIM1->enable();

  uint32_t volatile const fbData = reinterpret_cast<uint32_t const volatile>(&layerFrameBuffer);
  uint32_t const windowWidth = 240;
  uint32_t const windowHeight = 300;

  Compositor desktop({reinterpret_cast<void*>(fbData), windowWidth * windowHeight * sizeof(uint16_t)}, windowWidth, windowHeight);

  TextWindow textWindow(desktop, font::arialBold, {30, 20, 30 + 140, 20 + (16 * 3 - 8)}); //3.5 lines
  textWindow.setText("Naber? test test2");

  TextWindow textWindow2(desktop, font::arialBold, {0, 0, 16*8, 16});
  textWindow2.setText("0");

  TextWindow textWindow3(desktop, font::arialBold, {240 - 48, 0, 240, 16});
  textWindow3.setText("0");

  TextWindow adcWindow(desktop, font::arialBold, {0, 300 - 16, 240, 300});
  adcWindow.setText("ADC Result");

  I2C i2c(I2C::_3);

  //volatile RTC* rtc = RTC::open(RTC::ClockSource::LSI);
  volatile RTC rtc(RTC::ClockSource::LSI);

  volatile ADC adc(ADC::Module::_1);

  desktop.update();

  //adc.enableContinuous();
  auto tim = RCC::enablePeriph<RCC::TIM1>();

  while(true)
  {
    adc.startConversion();
    while(!adc.isEndOfConversion())
    { }

    static char adcResult[6];
    sprintf(adcResult, "%d", adc.getResult());
    adcWindow.setText(adcResult);
    adcWindow.update();

    static uint8_t i = 0;
    static char str[4];
    sprintf(str, "%d", i++);
    textWindow3.setText(str);
    textWindow3.update();

    static char time[9];
    sprintf(time, "%d%d:%d%d:%d%d", rtc.getHourTens(),rtc.getHourUnits(), rtc.getMinTens(),rtc.getMinUnits(), rtc.getSecTens(),rtc.getSecUnits());
    textWindow2.setText(time);
    textWindow2.update();

    uint16_t cntVal = TIM1->getCounterValue();
    if(cntVal >= std::numeric_limits<uint16_t>::max() / 2)
    {
      LCD::Color const green{0, 255, 0};
      //if(lcd0->getBgColor() != green)
      //  lcd0->setBgColor(green);
      portGpin13.set();
    }
    else
    {
      LCD::Color const red{255, 0, 0};
      //if(lcd0->getBgColor() != red)
      //  lcd0->setBgColor(red);
      portGpin13.reset();
    }
  }
}

bool exti0Handler()
{
  /*if(exti0->isPending())
  {
    if(!portGpin14.getOutputState())
     portGpin14.set();
    else
      portGpin14.reset();

  }
  exti0->clearPending();*/
}

/*extern "C" void EXTI0_IRQHandler()
{
  if(exti0->isPending())
  {
    if(!portGpin14->getOutputState())
     portGpin14->set();
    else
      portGpin14->reset();

    exti0->clearPending();
  }
}*/

bool exti3Handler()
{
  /*portGpin14.reset();
  exti2->clearPending();*/
}
