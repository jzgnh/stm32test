cmake_minimum_required(VERSION 3.12)

project(startup C ASM)

set(STARTUP_SRC)
set(SYSINIT_SRC)

if (MMOS_CHIPID)
  if(EXISTS "${PROJECT_SOURCE_DIR}/startup_${MMOS_CHIPID}.s")
    set(STARTUP_SRC "startup_${MMOS_CHIPID}.s")
  elseif(EXISTS "${PROJECT_SOURCE_DIR}/startup_${MMOS_CHIPID}.c")
    set(STARTUP_SRC  "startup_${MMOS_CHIPID}.c")
  endif()

  if(EXISTS "${PROJECT_SOURCE_DIR}/sysinit_${MMOS_CHIPID}.c")
    set(SYSINIT_SRC  "sysinit_${MMOS_CHIPID}.c")
  endif()
endif()

if(MMOS_FAMILY)
  if (NOT STARTUP_SRC)
    if(EXISTS "${PROJECT_SOURCE_DIR}/startup_${MMOS_FAMILY}.s")
      set(STARTUP_SRC "startup_${MMOS_FAMILY}.s")
    elseif(EXISTS "${PROJECT_SOURCE_DIR}/startup_${MMOS_FAMILY}.c")
      set(STARTUP_SRC  "startup_${MMOS_FAMILY}.c")
    endif()
  endif()

  if(NOT SYSINIT_SRC)
    if(EXISTS "${PROJECT_SOURCE_DIR}/sysinit_${MMOS_FAMILY}.c")
      set(SYSINIT_SRC  "sysinit_${MMOS_FAMILY}.c")
    endif()
  endif()
endif()


if(NOT STARTUP_SRC)
  set(STARTUP_SRC startup.c)
endif()

if(NOT SYSINIT_SRC)
  set(SYSINIT_SRC sysinit.c)
endif()

add_library(${PROJECT_NAME} OBJECT ${STARTUP_SRC} ${SYSINIT_SRC} _start.c)
target_link_libraries(${PROJECT_NAME} MCUTarget)
