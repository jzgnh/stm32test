cmake_minimum_required(VERSION 3.12)

include_guard(GLOBAL)

include(socs/stm32f1xx)


set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -T \"${CMAKE_CURRENT_LIST_DIR}/stm32f103x8.ld\"")
