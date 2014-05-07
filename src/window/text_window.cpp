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

#include <window/text_window.h>

#include <algorithm>
#include <cstring>

namespace stm32f429
{

TextWindow::TextWindow(Window& parent, Window& desktop, const uint8_t* const font, Area const area)
  : Window(parent, desktop, area)
  , m_font(font)
{ }

TextWindow& TextWindow::operator<<(std::string const& text)
{
  auto iterator = text.cbegin();
  while(iterator != text.cend())
  {
    *this << *iterator;
    ++iterator;
  }

  return *this;
}

TextWindow& TextWindow::operator<<(char const c)
{
  m_str.push_back(c);

  return *this;
}

std::pair<uint16_t, bool> const TextWindow::getPixel(std::size_t const x, std::size_t const y) const
{
  uint8_t const& charWidth = m_font[0];
  uint8_t const& charHeight = m_font[1];
  uint8_t const& lineHeight = charHeight;

  if(getWidth() < x || getHeight() < y)
    return {0, false};

  uint16_t const bitsPerChar = charWidth * charHeight;

  std::size_t const maxCharPerLine = getWidth() / charWidth;

  std::size_t const verticalSkippedChars = (y / lineHeight) * maxCharPerLine;
  std::size_t const horizontalSkippedChars = x / charWidth;

  uint8_t const& c = m_str[verticalSkippedChars + horizontalSkippedChars];

  uint8_t const* character = m_font + 4 + (c - 32) * (bitsPerChar / 8);

  bool const pixelState = character[((y % charHeight) * charWidth) / 8 + ((x % charWidth) / 8)] & (0x80 >>((x % charWidth) % 8));

  return {pixelState * 0xFF, true};

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
