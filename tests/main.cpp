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
#include <GPIO.h>
#include <RCC.h>
#include <SCB.h>
#include <SYSCFG.h>
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
  RCC::getReg<RCC::GPIOG>().enable();
  GPIO::getPeriph<GPIO::G>()->getPin<13>().setMode(GPIO::Periph<GPIO::G>::Pin<13>::Mode::Output);
  GPIO::getPeriph<GPIO::G>()->getPin<13>().set();

  //Port To Use With PWM TIM::_2
  RCC::RCC::getReg<RCC::GPIOB>().enable();
  auto gpioB = GPIO::getPeriph<GPIO::B>();
  auto PWMPin = gpioB->getPin<5>();
  PWMPin.setMode(GPIO::Periph<GPIO::B>::Pin<5>::Mode::Alternate);
  PWMPin.setAF(GPIO::Periph<GPIO::B>::Pin<5>::AF::_2);
  //PWMPin->setOutputSpeed(GPIO::Port<GPIO::PortB>::Pin<5>::OutputSpeed::Low);
  PWMPin.setPushPullMode(GPIO::Periph<GPIO::B>::Pin<5>::PushPullMode::PullUp);

  //birinde template ModuleInfo diğerinde uint8_t kullanılıyor ve ötekinde constexpr ile 4 byte'ı aşan offsetleme yapılıyor
  //çıkarılan assembly aynı
  RCC::getReg<RCC::GPIOG>().enable();
  RCC::getReg<RCC::TIM3>().enable();
  SYSCFG::getReg<SYSCFG::EXTI0>().setSource(SYSCFG::EXTI0::Source::PA);
  EXTI::getPeriph<EXTI::_0>().clearPending();

  //PWM
  RCC::getReg<RCC::TIM1>().enable();
  auto TIM3 = TIM::getPeriph<TIM::_3>();
  TIM3->enableAutoReloadPreload();
  auto TIM3CC2 = TIM3->getCC<2>();
  TIM3CC2.setValue(60);
  TIM3->setAutoReloadValue(120);
  TIM3CC2.setOCMode(TIM::Periph<TIM::_3>::CC<2>::OCMode::PWM1);
  TIM3CC2.enable();
  TIM3CC2.enableOCPreload();
  TIM3->generateEvent();
  TIM3->enable();

  //Configure EXTI0 to PA0 Rising Edge
  EXTI::getPeriph<EXTI::_0>().clearPending();
  SYSCFG::getReg<SYSCFG::EXTI0>().setSource(SYSCFG::EXTI0::Source::PA);
  EXTI::getPeriph<EXTI::_0>().disableInterruptMask();
  EXTI::getPeriph<EXTI::_0>().enableRisingTrigger();

  //Simple Loop Blink
  RCC::getReg<RCC::TIM6>().enable();
  TIM::getPeriph<TIM::_6>()->setAutoReloadValue(std::numeric_limits<uint16_t>::max());
  TIM::getPeriph<TIM::_6>()->setPrescalerValue(1000);
  TIM::getPeriph<TIM::_6>()->enable();

  EXTI::getPeriph<0>().clearPending();
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
