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

#include <window/compositor.h>

namespace stm32f429
{

uint8_t layerFrameBuffer[240 * 320 * sizeof(uint16_t)];

Compositor::Compositor(FrameBuffer const& fb, std::size_t const width, std::size_t const height)
  : Window(*this, *this, {0, 0, width, height})
  , m_frameBuffer(fb)
{ }

void Compositor::update()
{
  for(std::size_t y = 0; y < m_area.m_y2; ++y)
  {
    for(std::size_t x = 0; x < m_area.m_x2; ++x)
    {
      auto pixel = getPixel(x, y);

      if(pixel.second == false)
        continue;

      *reinterpret_cast<uint16_t*>(m_frameBuffer.buffer + (y * getWidth() + x) * sizeof(uint16_t)) = pixel.first;

      /*for(uint8_t i = 0; i < m_nSubWin; ++i)
      {
        bool isWindowValid = m_subWin[i]->getX() <= x && m_subWin[i]->getX2() >= x
            && m_subWin[i]->getY() <= y && m_subWin[i]->getY2() >= y;

        if(!isWindowValid)
          continue;

        auto pixel = m_subWin[i]->getPixel(x - m_subWin[i]->getX(), y - m_subWin[i]->getY());

        if(pixel.second == false)
          continue;

        *reinterpret_cast<uint16_t*>(m_frameBuffer.buffer + (y * getWidth() + x) * sizeof(uint16_t)) = pixel.first;
      }*/
    }
  }
}

}//NS stm32f429
