cmake_minimum_required(VERSION 3.12)


set(MMOS_BOARD TBB16-F103C8 CACHE STRING "Which board to build.")


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(borads/${MMOS_BOARD})

set(MMOS_CHIPID "${MMOS_DEF_CHIPID}" CACHE STRING "Which chip on the board.")
set(MMOS_FAMILY "${MMOS_DEF_FAMILY}" CACHE STRING "Chip family.")


set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/arm-none-gcc.cmake")



project(STM32Test C)

set(CMAKE_VERBOSE_MAKEFILE YES)

include_directories("${CMAKE_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/Include")
include_directories("${CMAKE_SOURCE_DIR}/cmsis/Core/Include")

add_compile_options(-Wall -Wno-unused-function)

include(Drivers/ConfigBSP.cmake)

add_subdirectory(libmmosc)

add_subdirectory(target)
add_subdirectory(Drivers)

add_subdirectory(startup)

add_executable(${PROJECT_NAME} main.c printf.c Trace.c)

target_link_options(${PROJECT_NAME} PRIVATE "-Wl,-Map=$<TARGET_FILE:${PROJECT_NAME}>.map")

target_link_libraries(${PROJECT_NAME} startup mmosc BSPTarget)

if (CMAKE_COMPILER_IS_GNUCC)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND "${ARM_GCC_OBJCOPY}" -O ihex $<TARGET_FILE:${PROJECT_NAME}> $<TARGET_FILE:${PROJECT_NAME}>.hex
                COMMAND "${ARM_GCC_OBJDUMP}" -htrD $<TARGET_FILE:${PROJECT_NAME}> > $<TARGET_FILE:${PROJECT_NAME}>.rMap)
endif()

