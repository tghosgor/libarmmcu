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

#include "include/system/exception.hpp"

namespace stm32f429
{
namespace exception
{

Error::Error(const char* const str) throw()
  : m_str(str)
{ }

Error::~Error() throw()
{ }

const char* const& Error::what() const throw()
{
  return m_str;
}

FatalError::FatalError(const char* const str) throw()
  : m_str(str)
{ }

FatalError::~FatalError() throw()
{ }

const char* const& FatalError::what() const throw()
{
  return m_str;
}

} //NS exception
} //NS stm32f429
