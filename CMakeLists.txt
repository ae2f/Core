cmake_minimum_required(VERSION 3.10)
project("Core")

# Namespace Package
include(GNUInstallDirs)

add_library(
	${PROJECT_NAME}
	"include/ae2f/Macro/Cast.h" 
	"include/ae2f/DataStructure/Allocator.h"
	"include/ae2f/DataStructure/Array.h"
	"include/ae2f/Macro/BitVector.h" 
	"include/ae2f/Macro/Compare.h"
	"src/DataStructure/cAllocator.c" 
	"include/ae2f/Macro/errGlobal.h" 
	"src/DataStructure/cArray.c"
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
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ae2f
)

# 패키지 구성 파일 생성
include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/CoreConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/CoreConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ae2f
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/CoreConfig.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ae2f
)