cmake_minimum_required(VERSION 3.12)

project(STM32F1xx_HAL_Driver C)


file(GLOB SRCS RELATIVE "${PROJECT_SOURCE_DIR}" "Inc/*.h" "Src/*.c")

GENERATE_HAL_CONF(stm32f1xx_hal_conf.h)
list(APPEND SRCS "${PROJECT_BINARY_DIR}/stm32f1xx_hal_conf.h")

add_library(${PROJECT_NAME} STATIC ${SRCS})

SET_HAL_DRIVER_INC(${PROJECT_NAME})
