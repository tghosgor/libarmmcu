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

#include "include/window/window.hpp"

#include "include/window/compositor.hpp"

#include <algorithm>

namespace stm32f429
{

Window::Window(Window& parent, Area const area)
  : Window(parent, parent.getCompositor(), area)
{ }

Window::Window(Window& parent, Compositor& compositor, Area const area)
  : m_parent(parent)
  , m_compositor(compositor)
  , m_area(area)
  , m_nSubWin(0)
{
  if(&parent != this)
    parent.m_subWin[parent.m_nSubWin++] = this;
}

Compositor&Window::getCompositor() { return m_compositor; }

void Window::bringToFront() const
{
  auto thisInParent = std::find(m_parent.m_subWin.begin(), m_parent.m_subWin.begin() + m_parent.m_nSubWin, this);

  std::move(m_parent.m_subWin.begin(), thisInParent, m_parent.m_subWin.begin() + 1);

  *m_parent.m_subWin.begin() = this;
}

void Window::sendToBack() const
{
  auto thisInParent = std::find(m_parent.m_subWin.begin(), m_parent.m_subWin.begin() + m_parent.m_nSubWin, this);

  std::move(thisInParent + 1, m_parent.m_subWin.begin() + m_parent.m_nSubWin, thisInParent);

  *(m_parent.m_subWin.begin() + m_parent.m_nSubWin) = this;
}

std::pair<uint16_t, bool> const Window::getPixel(std::size_t const x, std::size_t const y) const
{
  for(uint8_t i = 0; i < m_nSubWin; ++i)
  {
    bool const isWindowValid = m_subWin[i]->getX() <= x && m_subWin[i]->getX2() >= x
        && m_subWin[i]->getY() <= y && m_subWin[i]->getY2() >= y;

    if(!isWindowValid)
      continue;

    auto pixel = m_subWin[i]->getPixel(x - m_subWin[i]->getX(), y - m_subWin[i]->getY());

    if(pixel.second == false)
      continue;
    else
      return pixel;
  }

  //no subWin found on the pixel

  return {0, false};
}

void Window::update()
{
  m_compositor.render({getX(), getY(), getX2(), getY2()});
}

void Window::setX(std::size_t const x) { m_area.m_x = x; }
void Window::setX2(std::size_t const x2) { m_area.m_x2 = x2; }

void Window::setY(std::size_t const y) { m_area.m_y = y; }
void Window::setY2(std::size_t const y2) { m_area.m_y2 = y2; }

std::size_t const& Window::getX() const { return m_area.m_x; }
std::size_t const& Window::getX2() const { return m_area.m_x2; }

std::size_t const& Window::getY() const { return m_area.m_y; }
std::size_t const& Window::getY2() const { return m_area.m_y2; }

std::size_t const Window::getWidth() const { return getX2() - getX(); }
std::size_t const Window::getHeight() const { return getY2() - getY(); }

}//NS stm32f429
