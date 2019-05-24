
set(CMAKE_SYSTEM_NAME MMOS)
set(CMAKE_SYSTEM_PROCESSOR arm)

if(ARMGCC_HOME)
set(CMAKE_C_COMPILER "${ARMGCC_HOME}/bin/arm-none-eabi-gcc.exe")
set(CMAKE_CXX_COMPILER "${ARMGCC_HOME}/bin/arm-none-eabi-g++.exe")

set(ARM_GCC_OBJCOPY "${ARMGCC_HOME}/bin/arm-none-eabi-objcopy.exe")
set(ARM_GCC_OBJDUMP "${ARMGCC_HOME}/bin/arm-none-eabi-objdump.exe")
else()
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

set(ARM_GCC_OBJCOPY arm-none-eabi-objcopy)
set(ARM_GCC_OBJDUMP arm-none-eabi-objdump)
endif()

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -Wl,-Bstatic")

if(MMOS_CHIPID)
  string(TOLOWER "${MMOS_CHIPID}" MMOS_CHIPID)
  include(mcus/${MMOS_CHIPID})
endif()
