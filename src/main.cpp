
#include <GPIO.h>
#include <RCC.h>
#include <SCB.h>
#include <TIM.h>

#include <limits>

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
  portGpin13->setMode(GPIO::Port<GPIO::PortG>::Pin<13>::Mode::Output);
  portGpin13->set();
  //GPIO::getPort(GPIO::G)->getPin(13).set();

//  GPIO::get(GPIO::PortG)->m_MODER = 0x01 << 26;     /* Set GPIOG Pin 13 to output */
//  GPIO::get(GPIO::PortG)->m_BSRR |= 0x01 << 13;     /* Set GPIOG Pin 13 to ON */

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
  PWMPin->setMode(GPIO::Port<GPIO::PortB>::Pin<5>::Mode::Alternate);
  PWMPin->setAF(GPIO::Port<GPIO::PortB>::Pin<5>::AF::_2);
  //PWMPin->setOutputSpeed(GPIO::Port<GPIO::PortB>::Pin<5>::OutputSpeed::Low);
  PWMPin->setPushPullMode(GPIO::Port<GPIO::PortB>::Pin<5>::PushPullMode::PullUp);

  //PWM
  RCC::instance()->m_APB1ENR |= 0x1 <<1;      /* Enable the TIM2 */
  auto TIM3 = TIM::getTIM(TIM::_3);
  TIM::getTIM(TIM::_3)->enableAutoReloadPreload();
  TIM::getTIM(TIM::_3)->setCCValue<2>(60);
  TIM::getTIM(TIM::_3)->setAutoReloadValue(120);
  TIM::getTIM(TIM::_3)->setOCMode<2>(TIM::OCMode::PWM1);
  TIM::getTIM(TIM::_3)->enableCC<2>();
  TIM::getTIM(TIM::_3)->enableOCPreload<2>();
  TIM::getTIM(TIM::_3)->generateEvent();
  TIM::getTIM(TIM::_3)->enable();

  //Simple Loop Blink
  RCC::instance()->m_APB1ENR |= 0x1 <<4;      /* Enable the TIM6 */
  TIM::getTIM(TIM::_6)->setAutoReloadValue(std::numeric_limits<uint16_t>::max());
  TIM::getTIM(TIM::_6)->setPrescalerValue(1000);
  TIM::getTIM(TIM::_6)->enable();
  while(true)
  {
    uint16_t cntVal = TIM::getTIM(TIM::_6)->getCounterValue();
    if(cntVal >= std::numeric_limits<uint16_t>::max() / 2)
      GPIO::getPort<GPIO::PortG>()->getPin<13>()->set();
    else
      GPIO::getPort<GPIO::PortG>()->getPin<13>()->reset();
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
