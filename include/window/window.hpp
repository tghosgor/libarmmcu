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

#ifndef WINDOW_H_
#define WINDOW_H_

#include <cstdint>
#include <tuple>

namespace stm32f429
{

class Compositor;
class Window
{
public:
  struct Area
  {
    std::size_t m_x, m_y, m_x2, m_y2;
  };

public:
  Window(Window& parent, Area const area = {0, 0, 0, 0}); //TODO: any way to do , FrameBuffer const fb = parent.m_frameBuffer); ?
  Window(Window& parent, Compositor& compositor, Area const area = {0, 0, 0, 0});

  void bringToFront() const;
  void sendToBack() const;

  std::pair<uint16_t, bool> const virtual getPixel(std::size_t const x, std::size_t const y) const;
  void virtual update();

  void setX(std::size_t const x);
  void setX2(std::size_t const x2);

  void setY(std::size_t const y);
  void setY2(std::size_t const y2);

  std::size_t const& getX() const;
  std::size_t const& getX2() const;

  std::size_t const& getY() const;
  std::size_t const& getY2() const;

  std::size_t const getWidth() const;
  std::size_t const getHeight() const;

  Compositor& getCompositor();

protected:
  Window& m_parent;
  Compositor& m_compositor;
  Area m_area;
  std::array<Window const*, 16> m_subWin;
  uint8_t m_nSubWin;
};


}//NS stm32f429

#endif
