cmake_minimum_required(VERSION 3.12)

project(mmosc C)



file(GLOB_RECURSE SRCS RELATIVE "${PROJECT_SOURCE_DIR}" "src/*.h" "src/*.c" "src/*.cpp")

add_library(mmosc OBJECT ${SRCS})
