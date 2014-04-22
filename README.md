libarmmcu
=========

A C++ library interface to ARM MCUs and peripherals, initially only STM32F429I-DISCO is supported.

Syntax and usage example is shown in _tests/main.cpp_.

Peripheral access syntax is as follows:
```C++
auto portG = RCC::enablePeriph<RCC::GPIOG>();
auto portGpin13 = portG->createPin<13, GPIO::Port::PinMode::Output>();
portGpin13->set();

auto syscfg = RCC::enablePeriph<RCC::SYSCFG>();
auto exti0syscfg = syscfg->enable<SYSCFG::EXTI0>(); //Also enables NVIC
auto exti0 = exti0syscfg->setSource(SYSCFG::EXTISource::PA);
exti0->clearPending();
exti0->enableRisingTrigger();
exti0->enableInterrupt();
```


This project is incomplete and API is expected to change very quickly.
