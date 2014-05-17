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

#include <window/window.h>

#include <algorithm>

namespace stm32f429
{

Window::Window(Window& parent, Window& desktop, Area const area)
  : m_parent(parent)
  , m_compositor(desktop)
  , m_area(area)
  , m_nSubWin(0)
{
  if(&parent != this)
    parent.m_subWin[parent.m_nSubWin++] = this;
  //parent.attach(*this);
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

}//NS stm32f429
