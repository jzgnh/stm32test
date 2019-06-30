
project(BSPTarget C)

file(GLOB SRCS RELATIVE "${PROJECT_SOURCE_DIR}" "*.h" "*.c")

ADD_LIBRARY(BSPTarget OBJECT ${SRCS})

