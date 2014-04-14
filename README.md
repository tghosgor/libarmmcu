libarmmcu
=========

A C++ library interface to ARM MCUs and peripherals, initially only STM32F429I-DISCO is supported.

Syntax and usage example is shown in _tests/main.cpp_.

Peripheral access syntax are as follow:
```C++
GPIO::getPeriph<GPIO::G>()->getPin<13>().setMode(GPIO::Periph<GPIO::G>::Pin<13>::Mode::Output);
GPIO::getPeriph<GPIO::G>()->getPin<13>().set();
```

Control register access syntax are as follow:
```C++
RCC::getReg<RCC::GPIO>().enable<RCC::GPIO::B>();
SYSCFG::getReg<SYSCFG::EXTI>().setSource<SYSCFG::EXTI::_0>(SYSCFG::EXTI::Source::PA);
```

