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

#include <GPIO.h>
#include <RCC.h>
#include <SCB.h>
#include <TIM.h>

#include <limits>

using namespace stm32f429;

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

//  SCB::instance()->m_VTOR = 0x08000000; //VTOR Offset
}

int main()
{
  RCC::instance()->m_AHB1ENR |= 0x1 <<6;      /* Enable the GPIOG */
  auto gpioG = GPIO::getPort<GPIO::PortG>();
  auto portGpin13 = gpioG->getPin<13>();
  portGpin13.setMode(GPIO::Port<GPIO::PortG>::Pin<13>::Mode::Output);
  portGpin13.set();
  //GPIO::getPort(GPIO::G)->getPin(13).set();

//GPIO::get(GPIO::PortG)->m_MODER = 0x01 << 26;     /* Set GPIOG Pin 13 to output */
//GPIO::get(GPIO::PortG)->m_BSRR |= 0x01 << 13;     /* Set GPIOG Pin 13 to ON */

  /*GPIO::getPort(GPIO::G)->getPin<13>().setMode(GPIO::Port::Pin::Mode::Output);
  GPIO::getPort(GPIO::G)->getPin<14>().setMode(GPIO::Port::Pin::Mode::Output);

  GPIO::getPort(GPIO::G)->getPin<13>().set();
  uint32_t i = std::numeric_limits<uint16_t>::max() * 20;
  while(--i);
  GPIO::getPort(GPIO::G)->getPin<13>().reset();*/

  //Port To Use With PWM TIM::_2
  RCC::instance()->m_AHB1ENR |= 0x1 <<1;      /* Enable the GPIOB */
  auto gpioB = GPIO::getPort<GPIO::PortB>();
  auto PWMPin = gpioB->getPin<5>();
  PWMPin.setMode(GPIO::Port<GPIO::PortB>::Pin<5>::Mode::Alternate);
  PWMPin.setAF(GPIO::Port<GPIO::PortB>::Pin<5>::AF::_2);
  //PWMPin->setOutputSpeed(GPIO::Port<GPIO::PortB>::Pin<5>::OutputSpeed::Low);
  PWMPin.setPushPullMode(GPIO::Port<GPIO::PortB>::Pin<5>::PushPullMode::PullUp);

  //PWM
  RCC::instance()->m_APB1ENR |= 0x1 <<1;      /* Enable the TIM2 */
  auto TIM3 = TIM::getTIM<TIM::_3>();
  TIM3->enableAutoReloadPreload();
  auto TIM3CC2 = TIM3->getCC<2>();
  TIM3CC2.setValue(60);
  TIM3->setAutoReloadValue(120);
  TIM3CC2.setOCMode(TIM::TIM<TIM::_3>::CC<2>::OCMode::PWM1);
  TIM3CC2.enable();
  TIM3CC2.enableOCPreload();
  TIM3->generateEvent();
  TIM3->enable();

  //Simple Loop Blink
  RCC::instance()->m_APB1ENR |= 0x1 <<4;      /* Enable the TIM6 */
  TIM::getTIM<TIM::_6>()->setAutoReloadValue(std::numeric_limits<uint16_t>::max());
  TIM::getTIM<TIM::_6>()->setPrescalerValue(1000);
  TIM::getTIM<TIM::_6>()->enable();
  while(true)
  {
    uint16_t cntVal = TIM::getTIM<TIM::_6>()->getCounterValue();
    if(cntVal >= std::numeric_limits<uint16_t>::max() / 2)
      GPIO::getPort<GPIO::PortG>()->getPin<13>().set();
    else
      GPIO::getPort<GPIO::PortG>()->getPin<13>().reset();
  }
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
