
#include <RCC.h>
#include <GPIO.h>
#include <SCB.h>

int main()
{
  SCB::get()->m_VTOR = 0x08000000; //VTOR Offset
  RCC::get()->m_AHB1ENR |= 0x1 << 6;      /* Enable the GPIOG */
  GPIO::get(GPIO::Port::G)->m_MODER = 0x01 << 26;     /* Set GPIOG Pin 13 to output */
  GPIO::get(GPIO::Port::G)->m_BSRR |= 0x01 << 13;     /* Set GPIOG Pin 13 to ON */

  while(true);
}

