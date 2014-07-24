/*
  Copyright (c) 2014, Tolga HOŞGÖR
  All rights reserved.

  This file is part of libarmmcu.

  libarmmcu is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  libarmmcu is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with libarmmcu.  If not, see <http://www.gnu.org/licenses/>
*/

#ifndef TEXT_WINDOW_H_
#define TEXT_WINDOW_H_

#include "include/window/window.hpp"

namespace stm32f429
{

class TextWindow
  : public Window
{
public:
  TextWindow(Window& window, uint8_t const* const font, Area const area = {0, 0, 0, 0});

  void setText(char const* const cstr);

  std::pair<uint16_t, bool> const virtual getPixel(std::size_t const x, std::size_t const y) const override;

private:
  uint8_t const* m_font;
  char const* m_cstr;
  std::size_t m_cstrLen;
};

}//NS stm32f429

#endif
