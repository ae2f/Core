cmake_minimum_required(VERSION 3.20)
project(Core VERSION 6.25.19 LANGUAGES C CXX)
enable_testing()

include(cmake/Core.cmake)

if(NOT TARGET ae2f::${PROJECT_NAME})
    configure_file(${PROJECT_SOURCE_DIR}/hin/Pack/Num.h.in ${PROJECT_SOURCE_DIR}/inc/ae2f/Pack/Num.auto.h)
    configure_file(${PROJECT_SOURCE_DIR}/hin/Call.h.in ${PROJECT_SOURCE_DIR}/inc/ae2f/Call.auto.h)
    configure_file(${PROJECT_SOURCE_DIR}/hin/Float.h.in ${PROJECT_SOURCE_DIR}/inc/ae2f/Float.auto.h)
    configure_file(${PROJECT_SOURCE_DIR}/hin/LangVer.h.in ${PROJECT_SOURCE_DIR}/inc/ae2f/LangVer.auto.h)

    file(GLOB_RECURSE ae2f-core-inc ${PROJECT_SOURCE_DIR}/inc/*)
    file(GLOB_RECURSE ae2f-core-hin ${PROJECT_SOURCE_DIR}/hin/*)

    ae2f_CoreLibTent(
        ${PROJECT_NAME} INTERFACE inc ae2f
        ${ae2f-core-inc}
        ${ae2f-core-hin}
    )
    
    if(WIN32)
        set(ae2f-synchronization-needexd synchronization)
    else()
        set(ae2f-synchronization-needexd)
    endif()

    ae2f_CoreTestTent(ae2f-${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/test ${ae2f-synchronization-needexd})
    ae2f_CoreUtilityDocTent(${PROJECT_NAME} cmake ae2f)
endif()
