cmake_minimum_required(VERSION 3.12)

include_guard(GLOBAL)


include(socs/arm-v7m)

set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} -march=armv7e-m -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16")
