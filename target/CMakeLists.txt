cmake_minimum_required(VERSION 3.12)


macro(SET_HAL_DRIVER_INC ProjName)
    target_include_directories(${ProjName}  PUBLIC
        "${PROJECT_SOURCE_DIR}/../${MMOS_FAMILY}/Include"
        "${PROJECT_SOURCE_DIR}/Inc"
        "${PROJECT_SOURCE_DIR}"
        "${PROJECT_BINARY_DIR}")
    target_compile_definitions(${ProjName} PUBLIC -DUSE_FULL_LL_DRIVER)
endmacro()

macro(GENERATE_HAL_CONF tfile)
    if (EXISTS "${PROJECT_SOURCE_DIR}/${MMOS_CHIPID}_hal_conf.h.in")
        configure_file(${MMOS_CHIPID}_hal_conf.h.in ${tfile} @ONLY)
    elseif (EXISTS "${PROJECT_SOURCE_DIR}/${MMOS_CHIPID}_hal_conf.h")
        configure_file(${MMOS_CHIPID}_hal_conf.h ${tfile} COPYONLY)
    else()
        message(FALTAL_ERROR "Can not found HAL config file \"{MMOS_CHIPID}_hal_conf.h\" !")
    endif()
endmacro()



add_subdirectory(${MMOS_FAMILY}_HAL_Driver)

add_library(MCUTarget ALIAS ${MMOS_FAMILY}_HAL_Driver)

