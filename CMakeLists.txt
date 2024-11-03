cmake_minimum_required(VERSION 3.10)
project(Core)
enable_testing()

# Namespace Package
include(GNUInstallDirs) 

option(ae2f_IS_SHARED "Is a shared library or static one." OFF)


configure_file(${PROJECT_SOURCE_DIR}/hin/ae2f/Macro/Call.h.in ${PROJECT_SOURCE_DIR}/include/ae2f/Macro/Call.h)

add_library(
	${PROJECT_NAME}
    ${ae2f_PREFIX_LIB}

	"include/ae2f/Macro/Cast.h" 
	"include/ae2f/Macro/Cast/CasterUnion.hpp" 

    "include/ae2f/Macro/errGlob.h" 
    "include/ae2f/Macro/errGlob.hpp" 
    "src/Macro/errGlob.c"

    "include/ae2f/Macro/BitVec.h" 
	"include/ae2f/Macro/BitVec.hpp" 

	"include/ae2f/Ds/Alloc.h"
    "include/ae2f/Ds/Alloc.hpp"
	"src/Ds/Alloc.c" 
    "src/Ds/Alloc/Linear.c"

	"include/ae2f/Ds/Arr.h"
    "src/Ds/Arr.c"

	"include/ae2f/Macro/Compare.h"
	"include/ae2f/Macro/Compare.hpp"
    "include/ae2f/Macro/Call.h"
)

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

add_subdirectory(test)