cmake_minimum_required(VERSION 3.10)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY CACHE STRING "" FORCE)
project(Core VERSION 6.25.19 LANGUAGES C CXX)
enable_testing()

# Set this source directory as the tree root for project.
set(ae2f_ProjRoot ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "Tree root for project")
set(ae2f_submod  .submod CACHE STRING "Relative path to submodule (subdirectory)")
set(ae2f_CoreScript_Wh ${ae2f_ProjRoot}/${ae2f_submod}/ae2f/CoreScript)

# Execute git to fetch CoreScript when repository does not exist
if(NOT EXISTS ${ae2f_CoreScript_Wh})
	execute_process(
		COMMAND git clone https://codeberg.org/ae2f/CoreScript
		${ae2f_CoreScript_Wh}
		)
endif()

# add subdirectory
if(NOT TARGET ae2f::CoreScript)
	add_subdirectory(${ae2f_CoreScript_Wh} ${ae2f_submod}/ae2f/CoreScript)
endif()


if(ae2f_Core_RELOADED)
	set(_ae2f_Core_RELOADED ON)
else()
	set(_ae2f_Core_RELOADED OFF)
endif()

option(ae2f_Core_RELOADED	"ae2f::Core has been reloaded" ${ae2f_Core_N_RELOAD_ALWAYS})


if(NOT DEFINED CMAKE_C_STANDARD)
	set(ae2f_LangVer_C 90)
else()
	set(ae2f_LangVer_C ${CMAKE_C_STANDARD})
endif()

if(NOT DEFINED CMAKE_CXX_STANDARD)
	set(ae2f_LangVer_CC 98)
else()
	set(ae2f_LangVer_CC ${CMAKE_CXX_STANDARD})
endif()

include(CheckIncludeFile)
check_include_file(stdint.h HAVE_STDINT_H)

configure_file(
	${PROJECT_SOURCE_DIR}/inc/ae2f/c90/have-stdint.h.in
	${PROJECT_SOURCE_DIR}/inc/ae2f/c90/.have-stdint.h
	)

include(CheckTypeSize)
check_type_size("${ae2f_float}" ae2f_float_SZ)

configure_file(
	${PROJECT_SOURCE_DIR}/inc/ae2f/Pack/Num.h.in
	${PROJECT_SOURCE_DIR}/inc/ae2f/Pack/.Num.h
	)

configure_file(
	${PROJECT_SOURCE_DIR}/inc/ae2f/Call.h.in
	${PROJECT_SOURCE_DIR}/inc/ae2f/.Call.h
	)

configure_file(
	${PROJECT_SOURCE_DIR}/inc/ae2f/LangVer.h.in
	${PROJECT_SOURCE_DIR}/inc/ae2f/.LangVer.h
	)

configure_file(
	${PROJECT_SOURCE_DIR}/inc/ae2f/Float.h.in
	${PROJECT_SOURCE_DIR}/inc/ae2f/.Float.h
	)

configure_file(
	${PROJECT_SOURCE_DIR}/inc/ae2f/c90/ptrsz.h.in
	${PROJECT_SOURCE_DIR}/inc/ae2f/c90/.ptrsz.h
	)

configure_file(
	${PROJECT_SOURCE_DIR}/inc/ae2f/c90/ptrsz.h.in
	${PROJECT_SOURCE_DIR}/inc/ae2f/c90/.ptrsz.h
	)


check_type_size("char" SCHAR_WIDTH_BYTE)
check_type_size("unsigned char" UCHAR_WIDTH_BYTE)

check_type_size("short" SHRT_WIDTH_BYTE)
check_type_size("unsigned short" USHRT_WIDTH_BYTE)

check_type_size("int" INT_WIDTH_BYTE)
check_type_size("unsigned int" UINT_WIDTH_BYTE)

check_type_size("long" LONG_WIDTH_BYTE)
check_type_size("unsigned long" ULONG_WIDTH_BYTE)

check_type_size("long long" LLONG_WIDTH_BYTE)
check_type_size("unsigned long long" ULLONG_WIDTH_BYTE)

check_type_size("__int64" __INT64_WIDTH_BYTE)
check_type_size("unsigned __int64" __UINT64_WIDTH_BYTE)

configure_file(
	${PROJECT_SOURCE_DIR}/inc/ae2f/c90/limits.width.h.in
	${PROJECT_SOURCE_DIR}/inc/ae2f/c90/.limits.width.h
	)


if(NOT TARGET ae2f::Core)
	file(GLOB_RECURSE ae2f-core-inc ${PROJECT_SOURCE_DIR}/inc/*)
	ae2f_CoreLibTent(
		${PROJECT_NAME} INTERFACE inc ae2f
		${ae2f-core-inc}
		)

	if(WIN32)
		set(ae2f-synchronization-needexd synchronization)
	else()
		set(ae2f-synchronization-needexd)
	endif()

	ae2f_CoreTestTentVerbose(ae2f-${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/test ${ae2f-synchronization-needexd})
	ae2f_CoreUtilityDocTent(${PROJECT_NAME} cmake ae2f)
endif()
