/*
 * WWDG.h
 *
 *  Created on: Apr 4, 2014
 *      Author: Tolga HOŞGÖR
 */

#ifndef WWDG_H_
#define WWDG_H_

class WWDG
{
public:
  static volatile WWDG* instance() { return reinterpret_cast<volatile WWDG*>(0x40002C00); }

  union
  {
    uint32_t m_CR;
    struct
    {
      uint32_t m_T:7;
      bool WDGA:1;
    } __attribute__((__packed__));
  };

  union
  {
    uint32_t m_CFR;
  };

  bool m_SR:1;
};

#endif /* WWDG_H_ */
