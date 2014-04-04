
#include <RCC.h>
#include <GPIO.h>
#include <SCB.h>

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
  RCC::instance()->m_AHB1ENR |= 0x1 << 6;      /* Enable the GPIOG */
  GPIO::get(GPIO::Port::G)->m_MODER = 0x01 << 26;     /* Set GPIOG Pin 13 to output */
  GPIO::get(GPIO::Port::G)->m_BSRR |= 0x01 << 13;     /* Set GPIOG Pin 13 to ON */

  while(true);
}

extern "C" void _exit()
{
  while(true);
}
