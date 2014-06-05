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

#include <peripheral/ADC.hpp>
#include <register/EXTI.hpp>
#include <peripheral/I2C.hpp>
#include <register/IVTable.hpp>
#include <peripheral/GPIO.hpp>
#include <peripheral/LCD.hpp>
#include <register/NVIC.hpp>
#include <register/RCC.hpp>
#include <peripheral/RTC.hpp>
#include <register/SCB.hpp>
#include <register/SYSCFG.hpp>
#include <peripheral/TIM.hpp>

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

GPIO::Port portA(GPIO::Port::A);
GPIO::Port portB(GPIO::Port::B);
GPIO::Port portC(GPIO::Port::C);
GPIO::Port portD(GPIO::Port::D);
GPIO::Port portF(GPIO::Port::F);
GPIO::Port portG(GPIO::Port::G);
auto portGpin13 = portG.createPin(13, GPIO::Port::OutputPin);
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

  LCD lcd(portA, portB, portC, portD, portF, portG,
          ActiveWidth, hSync, HBP, HFP,
          ActiveHeight, vSync, VBP, VFP);
  //lcd0->setBgColor({255, 0, 0});
  lcd.setBgColor({255, 255, 255});

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

  void* const fbData = reinterpret_cast<void* const>(&layerFrameBuffer);
  constexpr uint32_t windowWidth = 240;
  constexpr uint32_t windowHeight = 300;

  Compositor desktop({fbData, windowWidth * windowHeight * sizeof(uint16_t)}, windowWidth, windowHeight);

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
  //adc.enableContinuous();

  GPIO::Port portB(GPIO::Port::B);
  auto tim43pwm = portB.createPin(6, GPIO::Port::AlternatePin);
  tim43pwm.setAF(GPIO::Port::AlPin::AF::_2);
  auto tim4 = RCC::enablePeriph<RCC::TIM4>();
  tim4->enableAutoReloadPreload();
  tim4->setAutoReloadValue(15000);
  tim4->getCC<1>().setOCMode(TIM::Periph<TIM::_4>::CC<1>::OCMode::PWM1);
  tim4->getCC<1>().setValue(1);
  tim4->getCC<1>().enableOCPreload();
  tim4->generateEvent();
  tim4->enable();
  tim4->getCC<1>().enable();

  desktop.update();

  while(true)
  {
    adc.startConversion();
    while(!adc.isEndOfConversion())
    { }

    auto adcResult = adc.getResult();

    tim4->getCC<1>().setValue((adcResult * 15000) / 4095);

    static char adcResultStr[6];
    sprintf(adcResultStr, "%d", adcResult);
    adcWindow.setText(adcResultStr);
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
      if(lcd.getBgColor() != green)
        lcd.setBgColor(green);
      portGpin13.set();
    }
    else
    {
      LCD::Color const red{255, 0, 0};
      if(lcd.getBgColor() != red)
        lcd.setBgColor(red);
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
