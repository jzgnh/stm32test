
include(Drivers/BSP/${MMOS_BOARD}/Config.cmake OPTIONAL)

if(EXISTS "${CMAKE_SOURCE_DIR}/Drivers/BSP/${MMOS_BOARD}/BSPConfig.h.in")
    configure_file(Drivers/BSP/${MMOS_BOARD}/BSPConfig.h.in
                   "${CMAKE_BINARY_DIR}/BSPConfig.h" @ONLY)
elseif(EXISTS "${CMAKE_SOURCE_DIR}/Drivers/BSP/${MMOS_BOARD}/BSPConfig.h")
    configure_file(Drivers/BSP/${MMOS_BOARD}/BSPConfig.h
                   "${CMAKE_BINARY_DIR}/BSPConfig.h" COPYONLY)
endif()

add_definitions(-D_MMOS_${MMOS_FAMILY})

string(REPLACE "-" "_" MMOSBOARDMACRO ${MMOS_BOARD})
add_definitions(-D_MMOS_BOARD_${MMOSBOARDMACRO})
if (EXISTS "${CMAKE_BINARY_DIR}/BSPConfig.h")
    include_directories("${CMAKE_BINARY_DIR}")
    add_compile_options(-include BSPConfig.h)
endif()

