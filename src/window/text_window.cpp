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

#include "include/window/text_window.hpp"

#include "include/window/compositor.hpp"

#include <algorithm>
#include <cstring>

namespace stm32f429
{

TextWindow::TextWindow(Window& parent, const uint8_t* const font, Area const area)
  : Window(parent, area)
  , m_font(font)
{ }

void TextWindow::setText(char const* const cstr)
{
  m_cstr = cstr;
  m_cstrLen = strlen(cstr);
}

std::pair<uint16_t, bool> const TextWindow::getPixel(std::size_t const x, std::size_t const y) const
{
  uint8_t const& charWidth = m_font[0];
  uint8_t const& charHeight = m_font[1];
  uint8_t const& lineHeight = charHeight;

  uint16_t const bitsPerChar = charWidth * charHeight;

  std::size_t const maxCharPerLine = getWidth() / charWidth;

  std::size_t const verticalSkippedChars = (y / lineHeight) * maxCharPerLine;
  std::size_t const horizontalSkippedChars = x / charWidth;

  if(verticalSkippedChars + horizontalSkippedChars >= m_cstrLen || horizontalSkippedChars >= maxCharPerLine)
    return {0, false};

  uint8_t const& c = m_cstr[verticalSkippedChars + horizontalSkippedChars];

  uint8_t const* character = m_font + 4 + (c - 32) * (bitsPerChar / 8);

  bool const pixelState = character[(x % charWidth) / 8 + (y % charHeight) * (charWidth / 8)] & (0x80 >>(x % 8));

  if(pixelState == true)
    return {0, true};
  else
    return {0, false};

  /*for(uint8_t height = 0; height < charHeight; ++height)
  {
    std::size_t const horizontalOffset = m_desktop.getWidth() * 2u * height;

    for(uint8_t width = 0; width < charWidth; ++width)
    {
      bool const pixelState = character[(height * charWidth) / 8 + (width / 8)] & (0x80 >>(width % 8));

      std::size_t const verticalOffset = width * 2u;

      *reinterpret_cast<uint16_t*>(m_desktop.getBuffer() + charFbOffset + verticalOffset + horizontalOffset) = pixelState * 0xFFFF;
    }
  }*/
}

}//NS stm32f429
