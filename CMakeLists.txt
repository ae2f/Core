cmake_minimum_required(VERSION 3.20)
project(Core VERSION 5.11.6 LANGUAGES C CXX)
enable_testing()

set(CMAKE_CXX_STANDARD 20)

option(ae2f_IS_SHARED "Is a shared library or static one." OFF)
option(ae2f_DOC "When activated, it would generate project with the deaders of cmake utility functions." OFF)
option(ae2f_TEST "When activated, it would generate test projects." ON)

set(ae2f_float float CACHE STRING "Float type for the template.")
set(ae2f_packcount 0 CACHE STRING "Pack count for pre-defined structures.")

if(ae2f_IS_SHARED)
    set(ae2f_LIBPREFIX SHARED CACHE STRING "SHARED")
else()
    set(ae2f_LIBPREFIX STATIC CACHE STRING "STATIC")
endif()

include(cmake/Utility.cmake)

if(NOT TARGET "${PROJECT_NAME}")
    configure_file(${PROJECT_SOURCE_DIR}/hin/Pack/Beg.h.in ${PROJECT_SOURCE_DIR}/include/ae2f/Pack/Beg.h)
    configure_file(${PROJECT_SOURCE_DIR}/hin/Pack/End.h.in ${PROJECT_SOURCE_DIR}/include/ae2f/Pack/End.h)
    configure_file(${PROJECT_SOURCE_DIR}/hin/Pack/Num.h.in ${PROJECT_SOURCE_DIR}/include/ae2f/Pack/Num.h)
    configure_file(${PROJECT_SOURCE_DIR}/hin/Call.h.in ${PROJECT_SOURCE_DIR}/include/ae2f/Call.h)
    configure_file(${PROJECT_SOURCE_DIR}/hin/Float.h.in ${PROJECT_SOURCE_DIR}/include/ae2f/Float.h)

    ae2f_CoreLibTent(
        ${PROJECT_NAME} INTERFACE include ae2f
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
        "include/ae2f/errGlob.hpp"
        "hin/Pack/Num.h.in"
        "include/ae2f/Pack/Num.h"
        "hin/Pack/Beg.h.in"
        "include/ae2f/Pack/Beg.h"
        "hin/Pack/End.h.in"
        "include/ae2f/Pack/End.h"
    )
    
    ae2f_CoreTestTent(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/test)
    ae2f_CoreUtilityDocTent(${PROJECT_NAME} cmake ae2f "cmake/Utility.hpp")
endif()