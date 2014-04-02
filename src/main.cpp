#include <RCC.h>
#include <GPIO.h>

int main()
{
  rcc->m_AHB1ENR |= 0x1 << 6;      /* Enable the GPIOG */
  gpioG->m_MODER = 0x01 << 26;     /* Set GPIOG Pin 13 to output */
  gpioG->m_BSRR |= 0x01 << 13;     /* Set GPIOG Pin 13 to ON */

  while(true);
}

