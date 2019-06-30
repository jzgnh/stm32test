cmake_minimum_required(VERSION 3.12)


set(MMOS_BOARD TBB16-F103C8 CACHE STRING "Which board to build.")


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(borads/${MMOS_BOARD})

set(MMOS_CHIPID "${MMOS_DEF_CHIPID}" CACHE STRING "Which chip on the board.")
set(MMOS_FAMILY "${MMOS_DEF_FAMILY}" CACHE STRING "Chip family.")


set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/arm-none-gcc.cmake")



project(STM32Test C)

set(CMAKE_VERBOSE_MAKEFILE YES)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# add_compile_options(-fshort-wchar)

include_directories("${CMAKE_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/Include")
include_directories("${CMAKE_SOURCE_DIR}/cmsis/Core/Include")

add_compile_options(-Wall -Wno-unused-function)

include(Drivers/ConfigBSP.cmake)

add_subdirectory(libmmosc)

add_subdirectory(target)
add_subdirectory(Drivers)

add_subdirectory(startup)


add_subdirectory(app)
