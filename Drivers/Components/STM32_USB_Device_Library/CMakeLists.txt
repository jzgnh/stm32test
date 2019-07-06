cmake_minimum_required(VERSION 3.12)

project(STM32_USB_Device_Library C)


link_libraries(MCUTarget)

file(GLOB SRCS RELATIVE "${PROJECT_SOURCE_DIR}" "Core/Inc/*.h" "Core/Src/*.c")

list(FILTER SRCS EXCLUDE REGEX "_template\.[ch]$")

add_library(${PROJECT_NAME} ${SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC
                            "${PROJECT_SOURCE_DIR}/Core/Inc")


if(IS_DIRECTORY "${PROJECT_SOURCE_DIR}/Class/${STM32_USB_DEV_CLS}")
    file(GLOB CLSSRCS RELATIVE "${PROJECT_SOURCE_DIR}"
            "Class/${STM32_USB_DEV_CLS}/Inc/*.h"
            "Class/${STM32_USB_DEV_CLS}/Src/*.c")


    list(FILTER CLSSRCS EXCLUDE REGEX "template\.c$")

    add_library(${PROJECT_NAME}_${STM32_USB_DEV_CLS} ${CLSSRCS})
    target_include_directories(${PROJECT_NAME}_${STM32_USB_DEV_CLS}
        PUBLIC "${PROJECT_SOURCE_DIR}/Class/${STM32_USB_DEV_CLS}/Inc"
        PRIVATE "${PROJECT_SOURCE_DIR}/Core/Inc")

    target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_${STM32_USB_DEV_CLS})
endif()


