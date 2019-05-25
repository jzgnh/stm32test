cmake_minimum_required(VERSION 3.12)

include_guard(GLOBAL)

#set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} -nostdinc")
#set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -nostdlib")

set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} --specs=nano.specs")

# -mabi=aapcs
set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} -mlittle-endian -mthumb -mno-unaligned-access")
