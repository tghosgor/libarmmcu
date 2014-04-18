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

namespace stm32f429
{
namespace GPIO
{

enum Address : std::size_t
{
  PortA = 0x40020000,
  PortB = 0x40020400,
  PortC = 0x40020800,
  PortG = 0x40021800
};

class Port
{
public: //Declarations
  enum class PinMode
  {
    Input = 0x0,
    Output = 0x1,
    Alternate = 0x2,
    Analog = 0x3
  };

  template<uint8_t nPin, PinMode mode>
  class Pin
  {
    enum class PullMode : uint32_t
    {
      None = 0x0,
      PullUp = 0x1,
      PullDown = 0x2
    };

    void setPullMode(PullMode const ppm) volatile;
  };

  template<uint8_t nPin>
  class Pin<nPin, (PinMode)1>
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
    void setOutputSpeed(OutputSpeed const ospeed) volatile;

    void set() volatile;
    void reset() volatile;

    bool getOutputState() volatile;
  }; //END OutputPin

public: //Methods
  template<uint8_t nPin, PinMode mode>
  Pin<nPin, mode> volatile* createPin() volatile;

public: //Registers
  uint32_t m_MODER;
  uint32_t m_OTYPER;
  uint32_t m_OSPEEDR;
  uint32_t m_PUPDR;
  uint32_t m_IDR;
  uint32_t m_ODR;
  uint32_t m_BSRR;
  uint32_t m_LCKR;
  uint32_t m_AFRL;
  uint32_t m_AFRH;

public:
  static constexpr std::size_t BaseAddress{ 0x40020000 };
}; //END Port

Port volatile* const createPort(std::size_t port);

template<uint8_t nPin>
class Port::Pin<nPin, Port::PinMode::Input>
{
  friend class Port;

public: //Declarations

public: //Methods
  bool getInputState() volatile;
}; //END InputPin

template<uint8_t nPin>
class Port::Pin<nPin, Port::PinMode::Alternate>
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
    Low,
    Medium,
    Fast,
    High
  };

public: //Methods
  void setAF(AF const af) volatile;
  void setOutputSpeed(OutputSpeed const ospeed) volatile;

private: //Internal Methods
  template<uint8_t idx_>
  typename std::enable_if<(idx_ < 8)>::type
  setAF_(AF const af) volatile;

  template<uint8_t idx_>
  typename std::enable_if<(idx_ >= 8 && idx_ <= 15)>::type
  setAF_(AF const af) volatile;
}; //END AFPin

} //NS GPIO
} //NS stm32f429

#include "impl/GPIO.impl"

#endif /* GPIO_H_ */


