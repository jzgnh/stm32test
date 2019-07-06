cmake_minimum_required(VERSION 3.12)

cmake_policy(SET CMP0079 NEW)

set(_DRIVER_ROOTDIR "${CMAKE_CURRENT_LIST_DIR}")

if(EXTRA_COMPONENTS)
    include_directories("${CMAKE_CURRENT_LIST_DIR}/Components/Inc")
    foreach(COMPNAME ${EXTRA_COMPONENTS})
        if (NOT EXISTS "${_DRIVER_ROOTDIR}/Components/${COMPNAME}/CMakeLists.txt")
            message(FATAL_ERROR "Can not found \"${COMPNAME}\" component.")
        endif()

        add_subdirectory(Components/${COMPNAME})
    endforeach()
endif()

if (NOT IS_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/BSP/${MMOS_BOARD}"
        OR NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/BSP/${MMOS_BOARD}/CMakeLists.txt")
    file(WRITE "${CMAKE_BINARY_DIR}/dummy.c" "")
    ADD_LIBRARY(BSPTarget STATIC "${CMAKE_BINARY_DIR}/dummy.c")
else()
    add_subdirectory(BSP/${MMOS_BOARD})
endif()

if(NOT TARGET BSPTarget)
    message(FATAL_ERROR "BSP must supply target named \"BSPTarget\"!")
endif()

target_link_libraries(BSPTarget MCUTarget)
if(EXTRA_COMPONENTS)
    target_link_libraries(BSPTarget ${EXTRA_COMPONENTS})
endif()

target_include_directories(BSPTarget PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/Components/Inc")
