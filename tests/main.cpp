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

#include <cstdint>
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
}

int main()
{
  RCC::getPeriph<RCC::GPIO::G>().enable();      /* Enable the B */
  auto gpioG = GPIO::getPeriph<GPIO::G>();
  auto portGpin13 = gpioG->getPin<13>();
  portGpin13.setMode(GPIO::GPIO<GPIO::G>::Pin<13>::Mode::Output);
  portGpin13.set();

  //Port To Use With PWM TIM::_2
  RCC::getPeriph<RCC::GPIO::B>().enable();      /* Enable the B */
  auto gpioB = GPIO::getPeriph<GPIO::B>();
  auto PWMPin = gpioB->getPin<5>();
  PWMPin.setMode(GPIO::GPIO<GPIO::B>::Pin<5>::Mode::Alternate);
  PWMPin.setAF(GPIO::GPIO<GPIO::B>::Pin<5>::AF::_2);
  //PWMPin->setOutputSpeed(GPIO::Port<GPIO::PortB>::Pin<5>::OutputSpeed::Low);
  PWMPin.setPushPullMode(GPIO::GPIO<GPIO::B>::Pin<5>::PushPullMode::PullUp);

  //PWM
  RCC::getPeriph<RCC::TIM::_3>().enable();      /* Enable the B */
  auto TIM3 = TIM::getPeriph<TIM::_3>();
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
  RCC::getPeriph<RCC::TIM::_6>().enable();      /* Enable the 6 */
  TIM::getPeriph<TIM::_6>()->setAutoReloadValue(std::numeric_limits<uint16_t>::max());
  TIM::getPeriph<TIM::_6>()->setPrescalerValue(1000);
  TIM::getPeriph<TIM::_6>()->enable();
  while(true)
  {
    uint16_t cntVal = TIM::getPeriph<TIM::_6>()->getCounterValue();
    if(cntVal >= std::numeric_limits<uint16_t>::max() / 2)
      GPIO::getPeriph<GPIO::G>()->getPin<13>().set();
    else
      GPIO::getPeriph<GPIO::G>()->getPin<13>().reset();
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
