cmake_minimum_required(VERSION 3.12)


macro(SET_HAL_DRIVER_INC ProjName)
    target_include_directories(${ProjName}  PUBLIC
        "${PROJECT_SOURCE_DIR}/../${MMOS_FAMILY}/Include"
        "${PROJECT_SOURCE_DIR}/Inc"
        "${PROJECT_SOURCE_DIR}")
    target_compile_definitions(${ProjName} PUBLIC -D_MMOS_${MMOS_FAMILY})
endmacro()


add_subdirectory(${MMOS_FAMILY}_HAL_Driver)

add_library(MCUTarget ALIAS ${MMOS_FAMILY}_HAL_Driver)

