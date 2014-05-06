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
  : m_utftFont(utftFont)
  , m_desktop(desktop)
{ }

void UTFT::writeCharacter(char const c, std::size_t offset)
{
  uint8_t const offsetInArr = 4 + (c - 32) * m_utftFont[3];
  //std::size_t const leftPadding = reinterpret_cast<std::size_t>(position) % m_desktop.getWidth();
  uint8_t height = m_utftFont[1];

  for(;height > 0; --height)
  {
    memcpy(m_desktop.getBuffer() + offset * m_utftFont[1], m_utftFont + offsetInArr, m_utftFont[0]);
    offset += m_desktop.getWidth() * 2u;
  }
}

}//NS font
}//NS stm32f429
