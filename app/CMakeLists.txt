cmake_minimum_required(VERSION 3.12)

set(APPNAME ${PROJECT_NAME})

project(appmain C)

include_directories("${PROJECT_SOURCE_DIR}"
                    "${PROJECT_SOURCE_DIR}/RC522")

file(GLOB_RECURSE SRCS RELATIVE "${PROJECT_SOURCE_DIR}" "*.h" "*.c")


add_executable(${APPNAME} ${SRCS})

target_link_options(${APPNAME} PRIVATE "-Wl,-Map=$<TARGET_FILE:${APPNAME}>.map")

target_link_libraries(${APPNAME} startup mmosc BSPTarget)

if (CMAKE_COMPILER_IS_GNUCC)
    add_custom_command(TARGET ${APPNAME} POST_BUILD
                COMMAND "${ARM_GCC_OBJCOPY}" -O ihex $<TARGET_FILE:${APPNAME}> $<TARGET_FILE:${APPNAME}>.hex
                COMMAND "${ARM_GCC_OBJDUMP}" -htrD $<TARGET_FILE:${APPNAME}> > $<TARGET_FILE:${APPNAME}>.rMap)
endif()

