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
