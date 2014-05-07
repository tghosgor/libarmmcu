project(libarmmcu)
cmake_minimum_required(VERSION 2.8)

enable_language(ASM)

#set(CMAKE_VERBOSE_MAKEFILE true)

set(CMAKE_SYSTEM_NAME "Bare Metal")
set(CMAKE_SYSTEM_PROCESSOR "ARM Cortex-M4")
set(CMAKE_AS_COMPILER "arm-none-eabi-gcc")
set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")
set(CMAKE_LINKER "arm-none-eabi-g++")
set(CMAKE_ASM_COMPILER "arm-none-eabi-as")

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type selected, defaulting to Debug.")
  set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_C_FLAGS "-std=c11 -mcpu=cortex-m4 -mthumb")
set(CMAKE_CXX_FLAGS "-std=c++11 -mcpu=cortex-m4 -mthumb -fno-exceptions")
set(CMAKE_CXX_FLAGS_DEBUG "-g1")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g1 -fno-inline")
set(CMAKE_ASM_FLAGS "-mcpu=cortex-m4 -mthumb")
set(CMAKE_ASM_FLAGS_RELEASE "")
set(CMAKE_ASM_FLAGS_RELWITHDEBINFO "")

set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "") #-rdynamic suppression
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "") #-rdynamic suppression

set(CMAKE_EXE_LINKER_FLAGS "-Xlinker --script ${libarmmcu_SOURCE_DIR}/misc/STM32F429ZI_FLASH.ld")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-s")

file(GLOB global_SRC
    "include/*.h"
    "src/*.cpp"
)

file(GLOB driver_SRC
    "include/driver/*.h"
    "src/driver/*.cpp"
)

file(GLOB window_SRC
    "include/window/*.h"
    "src/window/*.cpp"
)

file(GLOB font_SRC
    "include/font/*.h"
    "src/font/*.cpp"
)

include_directories(
  "include"
  "ext/freetype2/include"
)

#add_library(driver ${driver_SRC})
#add_library(window ${window_SRC})

add_executable(stm32f429i-disco tests/main.cpp misc/startup_stm32f429xx.S misc/STM32F429ZI_FLASH.ld ${driver_SRC} ${window_SRC} ${font_SRC} ${global_SRC} README.md)
#target_link_libraries(stm32f429i-disco driver_OBJ window_OBJ)

