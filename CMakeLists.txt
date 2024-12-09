cmake_minimum_required(VERSION 3.10)
project(Core VERSION 3.11.3 LANGUAGES C CXX)
enable_testing()

option(ae2f_IS_SHARED "Is a shared library or static one." OFF)
set(ae2f_float float CACHE STRING "Float type for the template.")
set(ae2f_packcount 0 CACHE STRING "Pack count for pre-defined structures.")

if(ae2f_IS_SHARED)
    set(ae2f_LIBPREFIX SHARED)
else()
    set(ae2f_LIBPREFIX STATIC)
endif()

# @brief
# Iterates a directory `prm_TestSourcesDir` and 
# Make a test case for every source.
# 
# @param prm_LibName
# Base Library name
# 
# @param prm_TestSourcesDir
# A directory where the stand-alone test codes locate. \n
# Every sources under that directory must be stand-alone, which means it must not depends on another memory, function, etc.
# 
# @param ...
# Additional Libraries if you want
function(ae2f_CoreTestTent prm_LibName prm_TestSourcesDir)
    file(GLOB_RECURSE files "${prm_TestSourcesDir}/*")
    list(LENGTH files list_length)
    
    math(EXPR adjusted_length "${list_length} - 1")

    foreach(i RANGE 0 ${adjusted_length})
        list(GET files ${i} item)
        add_executable("${prm_LibName}-Test${i}" ${item})
        target_link_libraries("${prm_LibName}-Test${i}" ${ARGN} ${prm_LibName})
        add_test(NAME "${prm_LibName}-Test${i}" COMMAND "${prm_LibName}${i}")
    endforeach()
endfunction()

# @brief
# Make a Library installable.
# 
# @param prm_TarName
# Library name you want.
# 
# @param prm_TarPrefix
# [STATIC | SHARED | INTERFACE]
# 
# @param ...
# The sources
function(ae2f_CoreLibProjTent prm_TarName prm_TarPreFix)
    # Namespace Package
    include(GNUInstallDirs)

    add_library(${prm_TarName} ${prm_TarPreFix} ${ARGN})

    # Install Settings
    install(TARGETS "${prm_TarName}"
        EXPORT ${prm_TarName}Targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
        
    install(DIRECTORY include/ae2f/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ae2f
    )

    # Package
    install(EXPORT ${prm_TarName}Targets
        FILE ${prm_TarName}Targets.cmake
        NAMESPACE ae2f::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
    )
        
    # Pack Conf
    include(CMakePackageConfigHelpers)
    configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/${prm_TarName}Config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
    )
        
    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${prm_TarName}Config.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
    )
endfunction()

if(NOT TARGET "${PROJECT_NAME}")
    configure_file(${PROJECT_SOURCE_DIR}/hin/Pack/Beg.h.in ${PROJECT_SOURCE_DIR}/include/ae2f/Pack/Beg.h)
    configure_file(${PROJECT_SOURCE_DIR}/hin/Pack/End.h.in ${PROJECT_SOURCE_DIR}/include/ae2f/Pack/End.h)
    configure_file(${PROJECT_SOURCE_DIR}/hin/Pack/Num.h.in ${PROJECT_SOURCE_DIR}/include/ae2f/Pack/Num.h)
    configure_file(${PROJECT_SOURCE_DIR}/hin/Call.h.in ${PROJECT_SOURCE_DIR}/include/ae2f/Call.h)
    configure_file(${PROJECT_SOURCE_DIR}/hin/Float.h.in ${PROJECT_SOURCE_DIR}/include/ae2f/Float.h)

    ae2f_CoreLibProjTent(
        ${PROJECT_NAME} INTERFACE 
        "hin/Call.h.in"
        "hin/Float.h.in"
        "include/ae2f/Cast.h"
        "include/ae2f/Cast/CasterUnion.hpp"
        "include/ae2f/Cast/Constexpr.hpp"
        "include/ae2f/BitVec.h"
        "include/ae2f/BitVec.hpp"
        "include/ae2f/Call.h"
        "include/ae2f/Cmp.h"    "include/ae2f/Cmp/Fun.h"
        "include/ae2f/Cmp.hpp"  "include/ae2f/Cmp/Fun.hpp"
        "include/ae2f/Float.h"
        "include/ae2f/errGlob.h"
        "hin/Pack/Num.h.in"
        "include/ae2f/Pack/Num.h"
        "hin/Pack/Beg.h.in"
        "include/ae2f/Pack/Beg.h"
        "hin/Pack/End.h.in"
        "include/ae2f/Pack/End.h"
    )

    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
    ae2f_CoreTestTent(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/test)
endif()