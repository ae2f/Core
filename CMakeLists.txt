cmake_minimum_required(VERSION 3.20)
project(Core VERSION 3.10.2 LANGUAGES C CXX)
enable_testing()

if(NOT TARGET ${PROJECT_NAME})

# Namespace Package
include(GNUInstallDirs)

option(ae2f_IS_SHARED "Is a shared library or static one." OFF)
set(ae2f_float float CACHE STRING "Float type for the template.")
set(ae2f_packcount 0 CACHE STRING "Pack count for pre-defined structures.")

if(ae2f_IS_SHARED)
    set(ae2f_LIBPREFIX SHARED)
else()
    set(ae2f_LIBPREFIX STATIC)
endif()

add_library(
    ${PROJECT_NAME}
    INTERFACE
    
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

configure_file(${PROJECT_SOURCE_DIR}/hin/Pack/Beg.h.in ${PROJECT_SOURCE_DIR}/include/ae2f/Pack/Beg.h)
configure_file(${PROJECT_SOURCE_DIR}/hin/Pack/End.h.in ${PROJECT_SOURCE_DIR}/include/ae2f/Pack/End.h)
configure_file(${PROJECT_SOURCE_DIR}/hin/Pack/Num.h.in ${PROJECT_SOURCE_DIR}/include/ae2f/Pack/Num.h)
configure_file(${PROJECT_SOURCE_DIR}/hin/Call.h.in ${PROJECT_SOURCE_DIR}/include/ae2f/Call.h)
configure_file(${PROJECT_SOURCE_DIR}/hin/Float.h.in ${PROJECT_SOURCE_DIR}/include/ae2f/Float.h)

add_subdirectory(test)
include_directories(include)

# Header
target_include_directories(${PROJECT_NAME}
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# 설치 설정
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
install(DIRECTORY include/ae2f/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ae2f
)

# 패키지 설정
install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ae2f::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
)
    
# 패키지 구성 파일 생성
include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
)
    
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)
    
endif()