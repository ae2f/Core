cmake_minimum_required(VERSION 3.10)

if(TARGET ae2f::Core)
	return()
endif()

if(${ae2f_CXX})
	project(Core VERSION 6.25.19 LANGUAGES C CXX)
else()
	project(Core VERSION 6.25.19 LANGUAGES C)
endif()

# Set this source directory as the tree root for project.
set(ae2f_ProjRoot ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "Tree root for project")
set(ae2f_BinRoot ${CMAKE_CURRENT_BINARY_DIR} CACHE STRING "Tree root for project")
set(ae2f_submod  .submod CACHE STRING "Relative path to submodule (subdirectory)")
set(ae2f_CoreScript_Wh ${ae2f_ProjRoot}/${ae2f_submod}/ae2f/CoreScript)

# Execute git to fetch CoreScript when repository does not exist
if(NOT EXISTS ${ae2f_CoreScript_Wh})
	execute_process(
		COMMAND git clone https://talkischeap.work.gd/ae2f/CoreScript
		${ae2f_CoreScript_Wh}
		)
endif()

# add subdirectory
if(NOT TARGET ae2f::CoreScript)
	add_subdirectory(${ae2f_CoreScript_Wh} ${ae2f_BinRoot}/${ae2f_submod}/ae2f/CoreScript)
endif()


enable_testing()

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

if(NOT DEFINED ae2f_NO_COMPILETEST)
	set(ae2f_NO_COMPILETEST 0)
endif()

include(CheckIncludeFile)
check_include_file(stdint.h HAVE_STDINT_H)
check_include_file(stdalign.h HAVE_STDALIGN_H)

if(ae2f_NO_COMPILETEST)
else()
	include(CheckTypeSize)
	macro(defnew	query varname)
		if(NOT DEFINED ${varname})
			check_type_size(${query} ${varname})
		endif()
	endmacro()

	defnew("${ae2f_float}" ae2f_float_SZ)
	defnew("void*" ae2f_SIZEOF_VOID_P)
	defnew("char" SCHAR_WIDTH_BYTE)
	defnew("unsigned char" UCHAR_WIDTH_BYTE)

	defnew("short" SHRT_WIDTH_BYTE)
	defnew("unsigned short" USHRT_WIDTH_BYTE)

	defnew("int" INT_WIDTH_BYTE)
	defnew("unsigned int" UINT_WIDTH_BYTE)

	defnew("long" LONG_WIDTH_BYTE)
	defnew("unsigned long" ULONG_WIDTH_BYTE)

	defnew("long long" LLONG_WIDTH_BYTE)
	defnew("unsigned long long" ULLONG_WIDTH_BYTE)

	defnew("__int64" __INT64_WIDTH_BYTE)
	defnew("unsigned __int64" __UINT64_WIDTH_BYTE)

	set(CMAKE_EXTRA_INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/dummy/enum.h)
	defnew("DUMMY_ENUM_ZERO" ENUMINT_WIDTH_BYTE)
	unset(CMAKE_EXTRA_INCLUDE_FILES)
endif()

macro(defnew	varname	default)
	if(NOT DEFINED ${varname} OR NOT ${varname})
		set(${varname} ${default})
	endif()
endmacro()

defnew(ae2f_float_SZ		0)
defnew(ae2f_SIZEOF_VOID_P	0)
defnew(SCHAR_WIDTH_BYTE		0)
defnew(UCHAR_WIDTH_BYTE		0)
defnew(SHRT_WIDTH_BYTE		0)
defnew(USHRT_WIDTH_BYTE		0)
defnew(INT_WIDTH_BYTE		0)
defnew(UINT_WIDTH_BYTE		0)
defnew(LONG_WIDTH_BYTE		0)
defnew(ULONG_WIDTH_BYTE		0)
defnew(LLONG_WIDTH_BYTE		0)
defnew(ULLONG_WIDTH_BYTE	0)
defnew(__INT64_WIDTH_BYTE	0)
defnew(__UINT64_WIDTH_BYTE	0)
defnew(ENUMINT_WIDTH_BYTE	0)
message(
	STATUS	"\n"
	"## ae2f::Core Configuration\n"
	"[ae2f_float_SZ]	${ae2f_float_SZ}\n"
	"[ae2f_SIZEOF_VOID_P]	${ae2f_SIZEOF_VOID_P}\n"
	"[SCHAR_WIDTH_BYTE]	${SCHAR_WIDTH_BYTE}\n"
	"[UCHAR_WIDTH_BYTE]	${UCHAR_WIDTH_BYTE}\n"
	"[SHRT_WIDTH_BYTE]	${SHRT_WIDTH_BYTE}\n"
	"[USHRT_WIDTH_BYTE]	${USHRT_WIDTH_BYTE}\n"
	"[INT_WIDTH_BYTE]	${INT_WIDTH_BYTE}\n"
	"[UINT_WIDTH_BYTE]	${UINT_WIDTH_BYTE}\n"
	"[LONG_WIDTH_BYTE]	${LONG_WIDTH_BYTE}\n"
	"[ULONG_WIDTH_BYTE]	${ULONG_WIDTH_BYTE}\n"
	"[LLONG_WIDTH_BYTE]	${LLONG_WIDTH_BYTE}\n"
	"[ULLONG_WIDTH_BYTE]	${ULLONG_WIDTH_BYTE}\n"
	"[__INT64_WIDTH_BYTE]	${__INT64_WIDTH_BYTE}\n"
	"[__UINT64_WIDTH_BYTE]	${__UINT64_WIDTH_BYTE}\n"
	"[ENUMINT_WIDTH_BYTE]	${ENUMINT_WIDTH_BYTE}\n"
	)

configure_file(
	${PROJECT_SOURCE_DIR}/inc/ae2f/c90/stdint/have.h.in
	${PROJECT_BINARY_DIR}/inc/ae2f/c90/stdint/.have.h
	)

configure_file(
	${PROJECT_SOURCE_DIR}/inc/ae2f/Pack/Num.h.in
	${PROJECT_BINARY_DIR}/inc/ae2f/Pack/.Num.h
	)

configure_file(
	${PROJECT_SOURCE_DIR}/inc/ae2f/Call.h.in
	${PROJECT_BINARY_DIR}/inc/ae2f/.Call.h
	)

configure_file(
	${PROJECT_SOURCE_DIR}/inc/ae2f/LangVer.h.in
	${PROJECT_BINARY_DIR}/inc/ae2f/.LangVer.h
	)

configure_file(
	${PROJECT_SOURCE_DIR}/inc/ae2f/Float.h.in
	${PROJECT_BINARY_DIR}/inc/ae2f/.Float.h
	)

configure_file(
	${PROJECT_SOURCE_DIR}/inc/ae2f/c90/ptrsz.h.in
	${PROJECT_BINARY_DIR}/inc/ae2f/c90/.ptrsz.h
	)

configure_file(
	${PROJECT_SOURCE_DIR}/inc/ae2f/c90/lmts/width.h.in
	${PROJECT_BINARY_DIR}/inc/ae2f/c90/lmts/.width.h
	)

if(NOT TARGET ae2f::Core)
	file(GLOB_RECURSE ae2f-core-inc ${PROJECT_SOURCE_DIR}/inc/*)
	ae2f_CoreLibTent(
		${PROJECT_NAME} INTERFACE inc ae2f
		${ae2f-core-inc}
		)
	target_include_directories(ae2f-Core INTERFACE $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/inc>)

	if(WIN32)
		set(ae2f-synchronization-needexd synchronization)
	else()
		set(ae2f-synchronization-needexd)
	endif()

	ae2f_CoreTestTentVerbose(ae2f-${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/test ${ae2f-synchronization-needexd})
	ae2f_CoreUtilityDocTent(${PROJECT_NAME} cmake ae2f)
	target_compile_definitions(ae2f-Core INTERFACE _CRT_SECURE_NO_WARNINGS)
endif()
