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

#ifndef GPIO_H_
#define GPIO_H_

#include <cstdint>
#include <type_traits>

#include <driver/fwd.hpp>

namespace stm32f429
{
namespace GPIO
{

enum : std::size_t
{
  PortA = 0x40020000,
  PortB = 0x40020400,
  PortC = 0x40020800,
  PortD = 0x40020C00,
  PortE = 0x40021000,
  PortF = 0x40021400,
  PortG = 0x40021800,
  PortH = 0x40021C00,
  PortI = 0x40022000
};

class Port
{
  friend class stm32f429::RCC;

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
  template<class PinType_>
  typename PinType_::type createPin(uint8_t const nPin, PinType_ const) volatile;

public: //Registers
  uint32_t m_MODER;
  uint32_t m_OTYPER;
  uint32_t m_OSPEEDR;
  uint32_t m_PUPDR;
  uint32_t m_IDR;
  uint32_t m_ODR;
  uint32_t m_BSRR;
  uint32_t m_LCKR;
  uint32_t m_AFR[2];

private:
  Port() { }
}; //END Port

class Port::Pin //Common Pin interface
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
  Pin(uint8_t const nPin, Port volatile& port);

protected:
  uint8_t const m_nPin;
  Port volatile& m_port;
}; //END Pin

class Port::InPin : public Pin
{
  friend class Port;

public: //Declarations

public: //Methods
  InPin(uint8_t const nPin, Port volatile& port);

  bool getInputState() volatile;

private:
  static constexpr uint8_t m_moder = 0x0;
}; //END InputPin

class Port::OuPin : public Pin
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
  OuPin(uint8_t const nPin, Port volatile& port);

  OuPin volatile& setOutputSpeed(OutputSpeed const ospeed) volatile;

  OuPin volatile& set() volatile;
  OuPin volatile& reset() volatile;

  bool getOutputState() volatile;

private:
  static constexpr uint8_t m_moder = 0x1;
}; //END OutputPin

class Port::AlPin : public Pin
{
  friend class Port;

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
  AlPin(uint8_t const nPin, Port volatile& port);

  AlPin volatile& setAF(AF const af) volatile;
  AlPin volatile& setOutputSpeed(OutputSpeed const ospeed) volatile;

private:
  static constexpr uint8_t m_moder = 0x2;
};

class Port::AnPin : public Pin
{
  friend class Port;

public:
  AnPin(uint8_t const nPin, Port volatile& port);
};

//END AFPin

} //NS GPIO
} //NS stm32f429

#endif /* GPIO_H_ */
