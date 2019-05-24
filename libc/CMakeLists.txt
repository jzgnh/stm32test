cmake_minimum_required(VERSION 3.12)

project(mc C)



# file(GLOB SRCS RELATIVE "${PROJECT_SOURCE_DIR}" "*.h" "*.c" "*.cpp")
# add_library(mbc ${SRCS})



file(GLOB_RECURSE SRCS RELATIVE "${PROJECT_SOURCE_DIR}" "src/*.h" "src/*.c" "src/*.cpp")

add_library(mc ${SRCS})
#target_link_libraries(mc INTERFACE c m gcc mbc)
target_link_libraries(mc INTERFACE c m gcc)
#target_link_libraries(mc mbc)
