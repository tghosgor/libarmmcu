/*
 * WWDG.h
 *
 *  Created on: Apr 4, 2014
 *      Author: Tolga HOŞGÖR
 */

#ifndef WWDG_H_
#define WWDG_H_

namespace stm32f429
{

class WWDG
{
public:
  static volatile WWDG* instance() { return reinterpret_cast<volatile WWDG*>(0x40002C00); }
};

} //NS stm32f429

#endif /* WWDG_H_ */
