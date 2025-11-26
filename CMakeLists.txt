cmake_minimum_required(VERSION 3.10)
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


if(NOT TARGET ae2f::Core)
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

	file(
		WRITE ${PROJECT_SOURCE_DIR}/inc/ae2f/c90/have-stdint.auto.h
		"#define HAVE_STDINT_H ${HAVE_STDINT_H}"
		)

	include(CheckTypeSize)
	check_type_size("${ae2f_float}" ae2f_float_SZ)

	file(
		WRITE ${PROJECT_SOURCE_DIR}/inc/ae2f/Pack/Num.auto.h
		"/**					\n"
		" * @file Num.auto.h			\n"
		" * @brief cmake-generated			\n"
		" **/					\n\n"

		"#define ae2f_PackCount ${ae2f_packcount}	\n"
		)

	file(
		WRITE ${PROJECT_SOURCE_DIR}/inc/ae2f/Call.auto.h
		"#undef ON	\n"
		"#undef OFF	\n"
		"#define OFF	0\n"
		"#define ON	1\n\n"

		"#undef ae2f_IS_SHARED \n"
		"/**					\n"
		" * @file Call.auto.h			\n"
		" * @brief cmake-generated			\n"
		" **/					\n\n"
		"#define ae2f_IS_SHARED ${ae2f_IS_SHARED}	\n"
		)

	file(
		WRITE ${PROJECT_SOURCE_DIR}/inc/ae2f/LangVer.auto.h
		"/**					\n"
		" * @file LangVer.auto.h			\n"
		" * @brief cmake-generated			\n"
		" **/					\n\n"

		"#if ${ae2f_LangVer_C} >= 50			\n"
		"#define ae2f_LangVer_C 19${ae2f_LangVer_C}		\n"
		"#else						\n"
		"#define ae2f_LangVer_C 20${ae2f_LangVer_C}		\n"
		"#endif						\n\n"

		"#if ${ae2f_LangVer_CC} >= 50			\n"
		"#define ae2f_LangVer_CC 19${ae2f_LangVer_CC}	\n"
		"#else						\n"
		"#define ae2f_LangVer_CC 20${ae2f_LangVer_CC}	\n"
		"#endif						\n\n"

		"#define __ae2f_lvcheck_c(v) (ae2f_LangVer_C >= (v))	\n"
		"#define __ae2f_lvcheck_cc(v) (ae2f_LangVer_CC >= (v))	\n"
		)

	file(
		WRITE ${PROJECT_SOURCE_DIR}/inc/ae2f/Float.auto.h
		"/** \n"
		"* @file Float.auto.h \n"
		"* @brief cmake-generated \n"
		"**/\n\n"

		"/** \n"
		"* @def ae2f_float \n"
		"* @brief Predefined floating point type\n"
		"**/\n"
		"#ifndef ae2f_float\n"
		"#define ae2f_float ${ae2f_float}\n"
		"#endif\n\n"

		"#ifndef ae2f_float_WIDTH\n"
		"#define ae2f_float_WIDTH (${ae2f_float_SZ} << 3)\n"
		"#endif\n"
		)

	file(
		WRITE "${PROJECT_SOURCE_DIR}/inc/ae2f/c90/ptrsz.auto.h"
		"/**					\n"
		" * @file ptrsz.auto.h			\n"
		" * @brief cmake-generated			\n"
		" **/					\n\n"

		"/**\n"
		" * @def ae2f_PTRSZ_SIZE\n"
		" * @brief Pointer size as bytes\n"
		" * @details Pointer size has been calculated by cmake.\n"
		" */\n"
		"#define ae2f_PTRSZ_SIZE ${CMAKE_SIZEOF_VOID_P}\n"
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

	file(
		WRITE
		"${PROJECT_SOURCE_DIR}/inc/ae2f/c90/limits.width.auto.h"
		"#ifndef SCHAR_WIDTH					\n"
		"#define SCHAR_WIDTH	(${SCHAR_WIDTH_BYTE} << 3)	\n"
		"#endif							\n\n"

		"#ifndef UCHAR_WIDTH					\n"
		"#define UCHAR_WIDTH	(${UCHAR_WIDTH_BYTE} << 3)	\n"
		"#endif							\n\n"

		"#ifndef SHRT_WIDTH						\n"
		"#define SHRT_WIDTH		(${SHRT_WIDTH_BYTE} << 3)	\n"
		"#endif							\n\n"

		"#ifndef USHRT_WIDTH					\n"
		"#define USHRT_WIDTH	(${USHRT_WIDTH_BYTE} << 3)	\n"
		"#endif							\n\n"

		"#ifndef INT_WIDTH						\n"
		"#define INT_WIDTH		(${INT_WIDTH_BYTE} << 3)	\n"
		"#endif							\n\n"

		"#ifndef UINT_WIDTH						\n"
		"#define UINT_WIDTH		(${UINT_WIDTH_BYTE} << 3)	\n"
		"#endif							\n\n"

		"#ifndef LONG_WIDTH						\n"
		"#define LONG_WIDTH		(${LONG_WIDTH_BYTE} << 3)	\n"
		"#endif							\n\n"

		"#ifndef ULONG_WIDTH					\n"
		"#define ULONG_WIDTH	(${ULONG_WIDTH_BYTE} << 3)	\n"
		"#endif							\n\n"
		)

	if(LLONG_WIDTH_BYTE)
		file(APPEND "${PROJECT_SOURCE_DIR}/inc/ae2f/c90/limits.width.auto.h"
			"#ifndef LLONG_WIDTH					\n"
			"#define LLONG_WIDTH	(${LLONG_WIDTH_BYTE} << 3)	\n"
			"#endif							\n\n"
			)
	else()
		file(APPEND "${PROJECT_SOURCE_DIR}/inc/ae2f/c90/limits.width.auto.h"
			"#ifndef LLONG_WIDTH					\n"
			"#define LLONG_WIDTH	(0)				\n"
			"#endif							\n\n"
			)
	endif()

	if(ULLONG_WIDTH_BYTE)
		file(APPEND "${PROJECT_SOURCE_DIR}/inc/ae2f/c90/limits.width.auto.h"
			"#ifndef ULLONG_WIDTH					\n"
			"#define ULLONG_WIDTH	(${ULLONG_WIDTH_BYTE} << 3)	\n"
			"#endif							\n\n"
			)
	else()
		file(APPEND "${PROJECT_SOURCE_DIR}/inc/ae2f/c90/limits.width.auto.h"
			"#ifndef ULLONG_WIDTH					\n"
			"#define ULLONG_WIDTH	(0)				\n"
			"#endif							\n\n"
			)
	endif()


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
