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

#include <font/utft.h>

#include <window/window.h>

#include <cstring>

namespace stm32f429
{
namespace font
{

UTFT::UTFT(uint8_t const* const utftFont, Window &desktop)
  : m_UTFTFont(utftFont)
  , m_desktop(desktop)
{ }

uint8_t const UTFT::writeCharacter(char const c, std::size_t const offset)
{
  uint8_t const& charWidth = m_UTFTFont[0];
  uint8_t const& charHeight = m_UTFTFont[1];
  uint16_t const bitsPerChar = charWidth * charHeight;
  uint8_t const* character = m_UTFTFont + 4 + (c - 32) * (bitsPerChar / 8);

  for(uint8_t height = 0; height < charHeight; ++height)
  {
    std::size_t const horizontalOffset = m_desktop.getWidth() * 2u * height;

    for(uint8_t width = 0; width < charWidth; ++width)
    {
      bool const pixelState = character[(height * charWidth) / 8 + (width / 8)] & (0x80 >>(width % 8));

      std::size_t const verticalOffset = width * 2u;

      *reinterpret_cast<uint16_t*>(m_desktop.getBuffer() + offset + verticalOffset + horizontalOffset) = pixelState * 0xFFFF;
    }
  }

  return charWidth;
}

}//NS font
}//NS stm32f429
