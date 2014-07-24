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

#ifndef GPIO_H_
#define GPIO_H_

#include <cstdint>
#include <type_traits>

#include "include/driver/util.hpp"
#include "include/driver/fwd.hpp"

namespace stm32f429
{

class GPIO
{
public:
  using Module = util::Module<1>;

  static const Module A;
  static const Module B;
  static const Module C;
  static const Module D;
  static const Module E;
  static const Module F;
  static const Module G;
  static const Module H;
  static const Module I;

private: //Internal Declarations
  template<uint8_t moder_, class typeName_>
  struct PinType
  {
    static constexpr uint8_t moder = moder_;
    using type = typeName_;
  };

public: //Declarations
  class Pin;
  class InPin;
  class OuPin;
  class AlPin;
  class AnPin;

  static constexpr PinType<0x0, InPin> InputPin{};
  static constexpr PinType<0x1, OuPin> OutputPin{};
  static constexpr PinType<0x2, AlPin> AlternatePin{};
  static constexpr PinType<0x3, AnPin> AnalogPin{};

public: //Methods
  GPIO(const Module& module);

  template<class PinType_>
  typename PinType_::type createPin(uint8_t const nPin, PinType_ const) volatile;

private: //Register
  struct Registers {
    uint32_t m_MODER;
    uint32_t m_OTYPER;
    uint32_t m_OSPEEDR;
    uint32_t m_PUPDR;
    uint32_t m_IDR;
    uint32_t m_ODR;
    uint32_t m_BSRR;
    uint32_t m_LCKR;
    uint32_t m_AFR[2];
  };

  Registers* m_registers;
}; //END GPIO

class GPIO::Pin //Common Pin interface
{
public:
  enum class PullMode : uint32_t
  {
    None = 0x0,
    PullUp = 0x1,
    PullDown = 0x2
  };

public: //Methods
  void setPullMode(PullMode const ppm) volatile;

protected:
  Pin(uint8_t const nPin, GPIO volatile& GPIO);

protected:
  uint8_t const m_nPin;
  GPIO volatile& m_GPIO;
}; //END Pin

class GPIO::InPin : public Pin
{
  friend class GPIO;

public: //Declarations

public: //Methods
  InPin(uint8_t const nPin, GPIO volatile& GPIO);

  bool getInputState() volatile;

private:
  static constexpr uint8_t m_moder = 0x0;
}; //END InputPin

class GPIO::OuPin : public Pin
{
public: //Declarations
  enum class OutputSpeed : uint32_t
  {
    Low,
    Medium,
    Fast,
    High
  };

public: //Methods
  OuPin(uint8_t const nPin, GPIO volatile& GPIO);

  OuPin volatile& setOutputSpeed(OutputSpeed const ospeed) volatile;

  OuPin volatile& set() volatile;
  OuPin volatile& reset() volatile;

  bool getOutputState() volatile;

private:
  static constexpr uint8_t m_moder = 0x1;
}; //END OutputPin

class GPIO::AlPin : public Pin
{
  friend class GPIO;

public: //Declarations
  enum class AF : uint32_t
  {
    _0, _1, _2, _3, _4,
    _5, _6, _7, _8, _9,
    _10, _11, _12, _13, _14,
    _15
  };

  enum class OutputSpeed : uint32_t
  {
    Low = 0,
    Medium = 1,
    Fast = 2,
    High = 3
  };

public: //Methods
  AlPin(uint8_t const nPin, GPIO volatile& GPIO);

  AlPin volatile& setAF(AF const af) volatile;
  AlPin volatile& setOutputSpeed(OutputSpeed const ospeed) volatile;

private:
  static constexpr uint8_t m_moder = 0x2;
};

class GPIO::AnPin : public Pin
{
  friend class GPIO;

public:
  AnPin(uint8_t const nPin, GPIO volatile& GPIO);
};

//END AFPin

} //NS stm32f429

#endif /* GPIO_H_ */
