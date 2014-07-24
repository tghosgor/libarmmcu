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

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include "include/driver/fwd.hpp"
#include "include/driver/util.hpp"

#include <cstdint>

namespace stm32f429
{
namespace exception
{

class Error
{
public:
  Error(const char* const str) throw();
  ~Error() throw();

  const char* const& what() const throw();

private:
  const char* const m_str;
};

class FatalError
{
public:
  FatalError(const char* const str) throw();
  ~FatalError() throw();

  const char* const& what() const throw();

private:
  const char* const m_str;
};

} //NS exception
} //NS stm32f429

#endif /* EXCEPTION_H_ */
