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

#include <EXTI.h>
#include <IVTable.h>
#include <GPIO.h>
#include <LCD.h>
#include <RCC.h>
#include <NVIC.h>
#include <SCB.h>
#include <SYSCFG.h>
#include <TIM.h>

#include <cstring>
#include <cstdint>
#include <limits>

using namespace stm32f429;

bool exti0Handler();
bool exti3Handler();

extern "C" void SystemInit()
{
  /* Reset the RCC clock configuration to the default reset state ------------*/
  /* Set HSION bit */
  RCC::instance()->m_CR |= (uint32_t)0x00000001;

  /* Reset CFGR register */
  RCC::instance()->m_CFGR = 0x00000000;

  /* Reset HSEON, CSSON and PLLON bits */
  RCC::instance()->m_CR &= (uint32_t)0xFEF6FFFF;

  /* Reset PLLCFGR register */
  RCC::instance()->m_PLLCFGR = 0x24003010;

  /* Reset HSEBYP bit */
  RCC::instance()->m_CR &= (uint32_t)0xFFFBFFFF;

  /* Disable all interrupts */
  RCC::instance()->m_CIR = 0x00000000;

  SCB::instance()->m_VTOR = reinterpret_cast<uint32_t>(&ivTable);
}

auto portA = RCC::enablePeriph<RCC::GPIOA>();
auto portApin0 = portA->createPin(0, GPIO::Port::InputPin);

auto portB = RCC::enablePeriph<RCC::GPIOB>();
auto portBpin2 = portB->createPin(2, GPIO::Port::InputPin);

auto portC = RCC::enablePeriph<RCC::GPIOC>();
auto portCpin2 = portC->createPin(2, GPIO::Port::InputPin);

auto portG = RCC::enablePeriph<RCC::GPIOG>();
auto portGpin13 = portG->createPin(13, GPIO::Port::OutputPin);
auto portGpin14 = portG->createPin(14, GPIO::Port::OutputPin);

auto syscfg = RCC::enablePeriph<RCC::SYSCFG>();
auto exti0syscfg = syscfg->enable<SYSCFG::EXTI0>();
auto exti0 = exti0syscfg->setSource(SYSCFG::EXTISource::PA);

auto extis2yscfg = syscfg->enable<SYSCFG::EXTI2>();
auto exti2 = extis2yscfg->setSource(SYSCFG::EXTISource::PC);

int main()
{
  portGpin13.set();

  SET_UP_TIM:
  auto TIM1 = RCC::enablePeriph<RCC::TIM1>();
  TIM1->setAutoReloadValue(std::numeric_limits<uint16_t>::max());
  TIM1->setPrescalerValue(1000);
  TIM1->enable();

  SET_UP_EXTI0:
  //Configure EXTI0 to PA0 Rising Edge
  portApin0.setPullMode(GPIO::Port::IPin::PullMode::PullDown);
  portCpin2.setPullMode(GPIO::Port::IPin::PullMode::PullDown);
  exti0->registerISR(&exti0Handler);
  exti0->clearPending();
  exti0->enableRisingTrigger();
  exti0->enableInterrupt();
  exti2->registerISR(&exti3Handler);
  exti2->clearPending();
  exti2->enableRisingTrigger();
  exti2->enableInterrupt();

  SET_UP_LCD:
  auto portD = RCC::enablePeriph<RCC::GPIOD>();
  auto portE = RCC::enablePeriph<RCC::GPIOE>();
  auto portF = RCC::enablePeriph<RCC::GPIOF>();
  auto portH = RCC::enablePeriph<RCC::GPIOH>();
  auto portI = RCC::enablePeriph<RCC::GPIOI>();

 /* portC->createPin<6, GPIO::Port::PinMode::Alternate>()->setAF(GPIO::Port::Pin<6, GPIO::Port::PinMode::Alternate>::AF::_14);//HSYNC
  portA->createPin<4, GPIO::Port::PinMode::Alternate>()->setAF(GPIO::Port::Pin<4, GPIO::Port::PinMode::Alternate>::AF::_14);//VSYNC

  portG->createPin<7, GPIO::Port::PinMode::Alternate>()->setAF(GPIO::Port::Pin<7, GPIO::Port::PinMode::Alternate>::AF::_14);//CLK
  portF->createPin<10, GPIO::Port::PinMode::Alternate>()->setAF(GPIO::Port::Pin<10, GPIO::Port::PinMode::Alternate>::AF::_14);//DE

  portC->createPin<10, GPIO::Port::PinMode::Alternate>()->setAF(GPIO::Port::Pin<10, GPIO::Port::PinMode::Alternate>::AF::_14);//R2
  portB->createPin<0, GPIO::Port::PinMode::Alternate>()->setAF(GPIO::Port::Pin<0, GPIO::Port::PinMode::Alternate>::AF::_14);//R3
  portA->createPin<11, GPIO::Port::PinMode::Alternate>()->setAF(GPIO::Port::Pin<11, GPIO::Port::PinMode::Alternate>::AF::_14);//R4
  portA->createPin<12, GPIO::Port::PinMode::Alternate>()->setAF(GPIO::Port::Pin<12, GPIO::Port::PinMode::Alternate>::AF::_14);//R5
  portB->createPin<1, GPIO::Port::PinMode::Alternate>()->setAF(GPIO::Port::Pin<1, GPIO::Port::PinMode::Alternate>::AF::_14);//R6
  portG->createPin<6, GPIO::Port::PinMode::Alternate>()->setAF(GPIO::Port::Pin<6, GPIO::Port::PinMode::Alternate>::AF::_14);//R7

  portA->createPin<6, GPIO::Port::PinMode::Alternate>()->setAF(GPIO::Port::Pin<6, GPIO::Port::PinMode::Alternate>::AF::_14);//G2
  portG->createPin<10, GPIO::Port::PinMode::Alternate>()->setAF(GPIO::Port::Pin<10, GPIO::Port::PinMode::Alternate>::AF::_14);//G3
  portB->createPin<10, GPIO::Port::PinMode::Alternate>()->setAF(GPIO::Port::Pin<10, GPIO::Port::PinMode::Alternate>::AF::_14);//G4
  portB->createPin<11, GPIO::Port::PinMode::Alternate>()->setAF(GPIO::Port::Pin<11, GPIO::Port::PinMode::Alternate>::AF::_14);//G5
  portC->createPin<7, GPIO::Port::PinMode::Alternate>()->setAF(GPIO::Port::Pin<7, GPIO::Port::PinMode::Alternate>::AF::_14);//G6
  portD->createPin<3, GPIO::Port::PinMode::Alternate>()->setAF(GPIO::Port::Pin<3, GPIO::Port::PinMode::Alternate>::AF::_14);//G7

  portD->createPin<6, GPIO::Port::PinMode::Alternate>()->setAF(GPIO::Port::Pin<6, GPIO::Port::PinMode::Alternate>::AF::_14);//B2
  portG->createPin<11, GPIO::Port::PinMode::Alternate>()->setAF(GPIO::Port::Pin<11, GPIO::Port::PinMode::Alternate>::AF::_14);//B3
  portG->createPin<12, GPIO::Port::PinMode::Alternate>()->setAF(GPIO::Port::Pin<12, GPIO::Port::PinMode::Alternate>::AF::_14);//B4
  portA->createPin<3, GPIO::Port::PinMode::Alternate>()->setAF(GPIO::Port::Pin<3, GPIO::Port::PinMode::Alternate>::AF::_14);//B5
  portB->createPin<8, GPIO::Port::PinMode::Alternate>()->setAF(GPIO::Port::Pin<8, GPIO::Port::PinMode::Alternate>::AF::_14);//B6
  portB->createPin<9, GPIO::Port::PinMode::Alternate>()->setAF(GPIO::Port::Pin<9, GPIO::Port::PinMode::Alternate>::AF::_14);//B7*/

  constexpr unsigned ActiveWidth = 294;
  constexpr unsigned ActiveHeight = 266;

  constexpr unsigned hSync = 10;
  constexpr unsigned HBP = 20;
  constexpr unsigned HFP = 10;

  constexpr unsigned vSync = 2;
  constexpr unsigned VBP = 2;
  constexpr unsigned VFP = 4;

  {
    //RCC::instance()->m_CR |= 0x1 <<16; //HSEON
    //RCC::instance()->m_PLLCFGR |= 0x1 <<22; //PLL source is HSE
    RCC::instance()->m_PLLCFGR |= 8 <<0; //PLL division PLLM
    RCC::instance()->m_PLLCFGR |= 360 <<6; //PLL multiplication PLLN
    RCC::instance()->m_PLLCFGR &= ~(0x3 <<16); //PLL division for main system clock PLLP
    RCC::instance()->m_PLLCFGR |=  7 <<24; //PLL main division for usb otg fs, sdio, rng PLLQ
    RCC::instance()->m_CR |= 0x1 <<24; //PLLON

    RCC::instance()->enablePLLSAI();
    RCC::instance()->setPLLSAIMFactor(192);
    RCC::instance()->setPLLSAIDFactor(4);
    RCC::instance()->setPLLSAIDIVR(RCC::PLLSAIDIVR::_8);
    RCC::instance()->enablePLLSAI();
    while(!RCC::instance()->isPLLSAIReady())
    { }
    auto lcd0 = RCC::enablePeriph<RCC::LCD0>();
    lcd0->setBgColor(255, 0, 0);
    lcd0->setSync(hSync, vSync);;
    lcd0->setBackPorch(HBP, VBP);
    lcd0->setActiveWidth(hSync + HBP + ActiveWidth,
                         vSync + VBP + ActiveHeight);
    lcd0->setTotalWidth(hSync + HBP + ActiveWidth + HFP,
                        vSync + VBP + ActiveHeight + VFP);
    //lcd0->enable();
    lcd0->immediateReload();
  }

  while(true)
  {
    uint16_t cntVal = TIM1->getCounterValue();
    if(cntVal >= std::numeric_limits<uint16_t>::max() / 2)
      portGpin13.set();
    else
      portGpin13.reset();
  }
}

bool exti0Handler()
{
  if(exti0->isPending())
  {
    if(!portGpin14.getOutputState())
     portGpin14.set();
    else
      portGpin14.reset();

  }
  exti0->clearPending();
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
  portGpin14.reset();
  exti2->clearPending();
}

extern "C" void _exit()
{
  while(true);
}
extern "C" void _kill()
{
}
extern "C" void _getpid()
{
}
extern "C" void _sbrk()
{
}
extern "C" void _write()
{
}
extern "C" void _close()
{
}
extern "C" void _fstat()
{
}
extern "C" void _isatty()
{
}
extern "C" void _lseek()
{
}
extern "C" void _read()
{
}
