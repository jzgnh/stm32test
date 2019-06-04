cmake_minimum_required(VERSION 3.12)


file(GLOB_RECURSE SRCS RELATIVE "${PROJECT_SOURCE_DIR}/app" "*.h" "*.c")


add_executable(${PROJECT_NAME} ${SRCS})

target_link_options(${PROJECT_NAME} PRIVATE "-Wl,-Map=$<TARGET_FILE:${PROJECT_NAME}>.map")

target_link_libraries(${PROJECT_NAME} startup mmosc BSPTarget)

if (CMAKE_COMPILER_IS_GNUCC)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND "${ARM_GCC_OBJCOPY}" -O ihex $<TARGET_FILE:${PROJECT_NAME}> $<TARGET_FILE:${PROJECT_NAME}>.hex
                COMMAND "${ARM_GCC_OBJDUMP}" -htrD $<TARGET_FILE:${PROJECT_NAME}> > $<TARGET_FILE:${PROJECT_NAME}>.rMap)
endif()

