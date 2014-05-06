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

namespace stm32f429
{

class Window
{
public:
  struct FrameBuffer
  {
    void* buffer;
    std::size_t size;
  };

  struct Area
  {
    std::size_t m_x, m_y, m_width, m_height;
  };

public:
  Window(Window& parent, Area const area = {0, 0, 0, 0});

  void setX(std::size_t const x);
  void setY(std::size_t const y);
  void setWidth(std::size_t const width);
  void setHeight(std::size_t const height);

  std::size_t const& getX() const;
  std::size_t const& getY() const;
  std::size_t const& getWidth() const;
  std::size_t const& getHeight() const;

protected:
  FrameBuffer m_frameBuffer;
  Window& m_parent;
  Area m_area;
};


}//NS stm32f429

#endif
