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

#include "include/window/compositor.hpp"

namespace stm32f429
{

uint8_t layerFrameBuffer[240 * 320 * sizeof(uint16_t)];

Compositor::Compositor(FrameBuffer const& fb, std::size_t const width, std::size_t const height)
  : Window(*this, *this, {0, 0, width, height})
  , m_frameBuffer(fb)
{ }

void Compositor::render(Area const& area)
{
  for(std::size_t y = area.m_y; y < area.m_y2; ++y)
  {
    for(std::size_t x = area.m_x; x < area.m_x2; ++x)
    {
      auto pixel = getPixel(x, y);

      uint16_t* const fbPixel = reinterpret_cast<uint16_t*>(m_frameBuffer.buffer + (y * getWidth() + x) * sizeof(uint16_t));

      if(pixel.second == false)
        *fbPixel = m_defaultPixelColor;
      else
        *fbPixel = pixel.first;

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
