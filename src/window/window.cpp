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

namespace stm32f429
{

Window::Window(Window& parent,
               const Area area)
  : m_parent(parent)
  , m_area(area)
  , m_frameBuffer({parent.m_frameBuffer.buffer, area.m_width * area.m_height})
{ }

void Window::setX(std::size_t const x) { m_area.m_x = x; }

void Window::setY(std::size_t const y) { m_area.m_y = y; }

void Window::setWidth(std::size_t const width) { m_area.m_width = width; }

void Window::setHeight(std::size_t const height) { m_area.m_height = height; }

std::size_t const& Window::getX() const { return m_area.m_x; }

std::size_t const& Window::getY() const { return m_area.m_y; }

std::size_t const& Window::getWidth() const { return m_area.m_width; }

std::size_t const& Window::getHeight() const { return m_area.m_height; }

void* Window::getBuffer() { return m_frameBuffer.buffer; }

}//NS stm32f429
