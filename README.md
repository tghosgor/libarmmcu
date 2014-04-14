libarmmcu
=========

A C++ library interface to ARM MCUs and peripherals, initially only STM32F429I-DISCO is supported.

Syntax and usage example is shown in _tests/main.cpp_.

Peripheral access syntax is as follows:
```C++
RCC::getReg<RCC::GPIO>().enable<RCC::GPIO::G>();
GPIO::getPeriph<GPIO::G>()->enable();
GPIO::getPeriph<GPIO::G>()->getPin<13>().setMode(GPIO::Periph<GPIO::G>::Pin<13>::Mode::Output);
GPIO::getPeriph<GPIO::G>()->getPin<13>().set();

RCC::getReg<RCC::TIM>().enable<RCC::TIM::_3>();
TIM::getPeriph<TIM::_3>()->enable();
TIM::getPeriph<TIM::_3>()->getCC<2>().setOCMode(TIM::Periph<TIM::_3>::CC<2>::OCMode::PWM1);
```

Control register access syntax is as follows:
```C++
RCC::getReg<RCC::GPIO>().enable<RCC::GPIO::B>();
SYSCFG::getReg<SYSCFG::EXTI>().setSource<SYSCFG::EXTI::_0>(SYSCFG::EXTI::Source::PA);
```

