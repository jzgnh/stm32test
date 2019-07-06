
project(BSPTarget C)

set(USE_STUSTLIB    YES)

file(GLOB SRCS RELATIVE "${PROJECT_SOURCE_DIR}" "*.h" "*.c")

if(USE_STUSTLIB)
list(REMOVE_ITEM SRCS usbimp.c)
else()
list(FILTER SRCS EXCLUDE REGEX "usbd?_.*\.[ch]$")
endif()

ADD_LIBRARY(BSPTarget OBJECT ${SRCS})

