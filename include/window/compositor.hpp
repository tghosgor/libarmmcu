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

#ifndef COMPOSITOR_H_
#define COMPOSITOR_H_

#include "include/window/window.hpp"

namespace stm32f429
{

class Compositor
  : public Window
{
public:
  struct FrameBuffer
  {
    void* buffer;
    std::size_t size;
  };

public:
  Compositor(FrameBuffer const& fb, std::size_t const width, std::size_t const height);

  void render(Area const& area);

private:
  FrameBuffer const m_frameBuffer;
  uint16_t static constexpr m_defaultPixelColor = 0xFFFF;
};

}//NS stm32f429

#endif
