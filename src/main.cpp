
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
  GPIO::getPort<GPIO::Port::G>()->getPin<14>()->setMode(GPIO::PortType<GPIO::Port::G>::Pin<14>::Mode::Output);
  // GPIO::getPort(GPIO::G)->getPin(14).set();

//  GPIO::get(GPIO::Port::G)->m_MODER = 0x01 << 26;     /* Set GPIOG Pin 13 to output */
//  GPIO::get(GPIO::Port::G)->m_BSRR |= 0x01 << 13;     /* Set GPIOG Pin 13 to ON */

  /*GPIO::getPort(GPIO::G)->getPin<13>().setMode(GPIO::Port::Pin::Mode::Output);
  GPIO::getPort(GPIO::G)->getPin<14>().setMode(GPIO::Port::Pin::Mode::Output);

  GPIO::getPort(GPIO::G)->getPin<13>().set();
  uint32_t i = std::numeric_limits<uint16_t>::max() * 20;
  while(--i);
  GPIO::getPort(GPIO::G)->getPin<13>().reset();*/

  RCC::instance()->m_APB1ENR |= 0x1 <<4;      /* Enable the TIM6 */
  TIM::getTIM(TIM::_6)->setAutoReloadValue(std::numeric_limits<uint16_t>::max());
  TIM::getTIM(TIM::_6)->setPrescalerValue(1000);
  TIM::getTIM(TIM::_6)->enable();

  TIM::getTIM(TIM::_2)->enableCC<1>();
  TIM::getTIM(TIM::_2)->setOCMode<1>(TIM::OCMode::PWM1);
  TIM::getTIM(TIM::_2)->enableOCPreload<1>();
  TIM::getTIM(TIM::_2)->enableAutoReloadPreload();
  TIM::getTIM(TIM::_2)->generateEvent();
  TIM::getTIM(TIM::_2)->setCCValue<1>(20);
  TIM::getTIM(TIM::_2)->setAutoReloadValue(120);
  TIM::getTIM(TIM::_2)->enable();

  while(true)
  {
    uint16_t cntVal = TIM::getTIM(TIM::_6)->getCounterValue();
    if(cntVal >= std::numeric_limits<uint16_t>::max() / 2)
      GPIO::getPort<GPIO::Port::G>()->getPin<14>()->set();
    else
      GPIO::getPort<GPIO::Port::G>()->getPin<14>()->reset();
  }
}

extern "C" void _exit()
{
  while(true);
}
