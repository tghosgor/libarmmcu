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

#include "include/system/OS.hpp"

#include "include/driver/IVTable.hpp"

#include <sys/types.h>

namespace stm32f429
{
namespace OS
{

static const char* haltErrorMsg;

void halt(const char* errorMsg)
{
  haltErrorMsg = errorMsg;
  Default_Handler();
}

extern "C"
{

caddr_t _sbrk ( int incr )
{ }

void _exit()
{
}

void _kill()
{
}
void _getpid()
{
}
void _open()
{
}
void _write()
{
}
void _close()
{
}
void _fstat()
{
}
void _isatty()
{
}
void _lseek()
{
}
void _read()
{
}

}

}//NS OS
}//NS stm32f429
