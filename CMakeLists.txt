project(libarmmcu)
cmake_minimum_required(VERSION 2.8)

enable_language(ASM)

set(CMAKE_SYSTEM_NAME "Bare Metal")
set(CMAKE_SYSTEM_PROCESSOR "ARM")
set(CMAKE_AS_COMPILER "arm-none-eabi-gcc")
set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")
set(CMAKE_ASM_COMPILER "arm-none-eabi-as")

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type selected, defaulting to Debug.")
  set(CMAKE_BUILD_TYPE "Debug")
endif()

include_directories(include)

set(CMAKE_C_FLAGS "-std=c++11 -mcpu=cortex-m4 -mthumb")
set(CMAKE_CXX_FLAGS "-std=c++11 -mcpu=cortex-m4 -mthumb")
set(CMAKE_CXX_FLAGS_DEBUG "-g2")
set(CMAKE_ASM_FLAGS "-mcpu=cortex-m4 -mthumb")
set(CMAKE_ASM_FLAGS_RELEASE "")

set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "") #-rdynamic suppression

set(CMAKE_EXE_LINKER_FLAGS "-Xlinker --script ${libarmmcu_SOURCE_DIR}/misc/STM32F429ZI_FLASH.ld")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-s")

add_executable(stm32f429i-disco tests/main.cpp misc/startup_stm32f429xx.S misc/STM32F429ZI_FLASH.ld include/RCC.h include/SCB.h include/GPIO.h include/TIM.h include/ADC.h include/impl/GPIO.impl include/impl/TIM.impl include/impl/RCC.impl)

