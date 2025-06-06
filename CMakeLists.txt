cmake_minimum_required(VERSION 3.20)
project(Core VERSION 6.23.17 LANGUAGES C CXX)
enable_testing()

include(cmake/Core.cmake)

if(NOT TARGET "${PROJECT_NAME}")
    configure_file(${PROJECT_SOURCE_DIR}/hin/Pack/Num.h.in ${PROJECT_SOURCE_DIR}/include/ae2f/Pack/Num.auto.h)
    configure_file(${PROJECT_SOURCE_DIR}/hin/Call.h.in ${PROJECT_SOURCE_DIR}/include/ae2f/Call.auto.h)
    configure_file(${PROJECT_SOURCE_DIR}/hin/Float.h.in ${PROJECT_SOURCE_DIR}/include/ae2f/Float.auto.h)

    ae2f_CoreLibTent(
        ${PROJECT_NAME} INTERFACE include ae2f
        "hin/Float.h.in"
	"include/ae2f/Float.h"
	"include/ae2f/Float.auto.h"

        "include/ae2f/Cast.h"
        "include/ae2f/Cast/CasterUnion.hpp"
        "include/ae2f/Cast/Constexpr.hpp"

        "include/ae2f/BitVec.h"
        "include/ae2f/BitVec.hpp"

	"hin/Call.h.in"
        "include/ae2f/Call.h"

        "include/ae2f/Cmp.h"    "include/ae2f/Cmp/Fun.h"
        "include/ae2f/Cmp.hpp"  "include/ae2f/Cmp/Fun.hpp"

        "include/ae2f/errGlob.h"
        "include/ae2f/errGlob.hpp"

        "hin/Pack/Num.h.in"
        "include/ae2f/Pack/Num.h"
        "include/ae2f/Pack/Num.auto.h"
        "include/ae2f/Pack/Beg.h"
        "include/ae2f/Pack/End.h"

        "include/ae2f/Atom.h"
        "include/ae2f/WaitWake.h"
    )
    
    ae2f_CoreTestTent(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/test)
    ae2f_CoreUtilityDocTent(${PROJECT_NAME} cmake ae2f)
endif()
