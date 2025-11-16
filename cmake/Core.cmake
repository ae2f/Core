option(ae2f_IS_SHARED "Is a shared library or static one." OFF)
option(ae2f_DOC "When activated, it would generate project with the deaders of cmake utility functions." OFF)
option(ae2f_TEST "When activated, it would generate test projects." ON)
option(ae2f_CXX "Tell that thou art including cxx for thy project." ON)
option(ae2f_nakedalais "alais naked on ae2f_CoreLibTentConfigCustom" OFF)

set(ae2f_float float CACHE STRING "Float type for the template.")
set(ae2f_packcount 0 CACHE STRING "Pack count for pre-defined structures.")
set(ae2f_ProjRoot ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "Current Source Root")
set(ae2f_BinRoot ${CMAKE_CURRENT_BINARY_DIR} CACHE STRING "Current Binary Root")
set(ae2f_submod  submod CACHE STRING submod)

if(ae2f_IS_SHARED)
	set(ae2f_LIBPREFIX SHARED CACHE STRING "SHARED")
else()
	set(ae2f_LIBPREFIX STATIC CACHE STRING "STATIC")
endif()

function(ae2f_UltraError TARGET FLAG TEST_NAME)
	message("UltraError for ${TARGET}")
	macro(gnu_asan PRM_C_COMPILER_ID PRM_CXX_COMPILER_ID PRM_C_COMPILER PRM_CXX_COMPILER)
		set(_gnu_asan OFF)

		if(LINUX)
			execute_process(
				COMMAND ${PRM_C_COMPILER} -print-file-name=libasan.so
				OUTPUT_VARIABLE	_libsan_path
				)
			set(_gnu_asan ON)
		elseif(APPLE)
			execute_process(
				COMMAND ${PRM_C_COMPILER} -print-file-name=libasan.dylib
				OUTPUT_VARIABLE	_libsan_path
				)
			set(_gnu_asan ON)
		endif()

		if(_gnu_asan)
			string(REGEX REPLACE "[ \t\n\r]+" "" libsan_path "${_libsan_path}")
			set(asan_flag -fsanitize=address -fsanitize=undefined)
		endif()

		if(TEST_NAME)
			set_tests_properties(
				${TEST_NAME} PROPERTIES
				ENVIRONMENT "LD_PRELOAD=${libsan_path}"
				)
		endif()
	endmacro(gnu_asan)

	macro(gnu PRM_C_COMPILER_ID PRM_CXX_COMPILER_ID PRM_C_COMPILER PRM_CXX_COMPILER)
		set(gnu-flag)
		set(gnu-flag-c)
		set(gnu-flag-cc)
		set(gnu-flag-lnk)

		if(${PRM_C_COMPILER_ID} STREQUAL "GNU")
			set(gnu-flag-c
				-Wstrict-prototypes 
				-Wmissing-prototypes 
				-Wnested-externs
				-Wold-style-definition 
				-Wunsuffixed-float-constants
				)
		endif()

		if(${PRM_CXX_COMPILER_ID} STREQUAL "GNU")
			set(gnu-flag-cc
				-Wold-style-cast 
				-Woverloaded-virtual 
				-Wnon-virtual-dtor
				-Wsuggest-override
				-Wuseless-cast 
				-Wcomment 
				-Wreorder 
				-Wnoexcept
				)
		endif()

		if(${PRM_C_COMPILER_ID} STREQUAL "GNU" AND ${PRM_CXX_COMPILER_ID} STREQUAL "GNU")
			gnu_asan(${PRM_C_COMPILER_ID} ${PRM_CXX_COMPILER_ID} ${PRM_C_COMPILER} ${PRM_CXX_COMPILER})

			set(gnu-flag
				${asan_flag}
				-Wall -Wextra -Werror -Wpedantic
				-Wshadow 
				-Wfloat-equal -Wundef 
				-Wcast-align=strict
				-Wconversion 
				-Wsign-conversion 
				-Wnull-dereference
				-Wformat=2 -Wformat-signedness -Wformat-truncation
				-Wimplicit-fallthrough=5 -Wswitch-enum -Wswitch-default
				-Wvla -Wduplicated-cond -Wduplicated-branches -Wlogical-op
				-Warith-conversion -Wmissing-declarations
				-D_GLIBCXX_ASSERTIONS
				-fstrict-flex-arrays=3 -fstack-protector-strong -fstack-clash-protection
				-fanalyzer -ftrivial-auto-var-init=zero
				)
			set(
				gnu-flag-lnk
				${asan_flag}
				)
		endif()
	endmacro(gnu)

	macro(clang PRM_C_COMPILER_ID PRM_CXX_COMPILER_ID PRM_C_COMPILER PRM_CXX_COMPILER)
		set(clang-flag)
		set(clang-flag-c)
		set(clang-flag-cc)
		set(clang-flag-lnk)

		if(${PRM_C_COMPILER_ID} STREQUAL "Clang" AND ${PRM_CXX_COMPILER_ID} STREQUAL "Clang")
		endif()
	endmacro(clang)

	get_target_property(ccid-c ${TARGET} C_COMPILER_ID)
	get_target_property(ccid-cc ${TARGET} CXX_COMPILER_ID)

	get_target_property(cc-c ${TARGET} C_COMPILER)
	get_target_property(cc-cc ${TARGET} CXX_COMPILER)

	if(ccid-c STREQUAL "ccid-c-NOTFOUND")
		set(ccid-c ${CMAKE_C_COMPILER_ID})
	endif()
	if(ccid-cc STREQUAL "ccid-cc-NOTFOUND")
		set(ccid-cc ${CMAKE_CXX_COMPILER_ID})
	endif()

	if(cc-c STREQUAL "cc-c-NOTFOUND")
		set(cc-c ${CMAKE_C_COMPILER})
	endif()
	if(cc-cc STREQUAL "cc-cc-NOTFOUND")
		set(cc-cc ${CMAKE_CXX_COMPILER})
	endif()


	gnu(${ccid-c} ${ccid-cc} ${cc-c} ${cc-cc})
	clang(${ccid-c} ${ccid-cc} ${cc-c} ${cc-cc})

	target_compile_options(${TARGET} ${FLAG}
		${gnu-flag}
		${clang-flag}

		$<$<COMPILE_LANGUAGE:CXX>:
		${gnu-flag-cc}
		${clang-flag-cc}
		>
		$<$<COMPILE_LANGUAGE:C>:
		${gnu-flag-c}
		${clang-flag-c}
		>
		)

	target_link_options(${TARGET} ${FLAG}
		${gnu-flag-lnk}
		${clang-flag-lnk}
		)
endfunction()

# @namespace ___DOC_CMAKE
# @brief
# Note they functions defined on CMake, not C/C++.
# 
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
# 
# @see ___DOC_CMAKE::ae2f_TEST
function(ae2f_CoreTestTent prm_LibName prm_TestSourcesDir)
	if(ae2f_TEST)
		if(ae2f_CXX)
			file(GLOB_RECURSE files "${prm_TestSourcesDir}/*")
		else()
			file(GLOB_RECURSE files "${prm_TestSourcesDir}/*.c")
		endif()

		foreach(item IN LISTS files)
			get_filename_component(__NAME ${item} NAME)
			add_executable("${prm_LibName}-Test-${__NAME}" ${item})
			target_link_libraries("${prm_LibName}-Test-${__NAME}" PRIVATE ${ARGN} ${prm_LibName})
			add_test(NAME "${prm_LibName}-Test-${__NAME}" COMMAND "${prm_LibName}-Test-${__NAME}")
		endforeach()
	endif()
endfunction()

# @namespace ___DOC_CMAKE
# @brief
# Note they functions defined on CMake, not C/C++.
# 
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
# 
# @see ___DOC_CMAKE::ae2f_TEST
function(ae2f_CoreTestTentVerbose prm_LibName prm_TestSourcesDir)
	if(ae2f_TEST)
		if(ae2f_CXX)
			file(GLOB_RECURSE files "${prm_TestSourcesDir}/*")
		else()
			file(GLOB_RECURSE files "${prm_TestSourcesDir}/*.c")
		endif()

		foreach(item IN LISTS files)
			get_filename_component(__NAME ${item} NAME)
			add_executable("${prm_LibName}-Test-${__NAME}" ${item})
			target_link_libraries("${prm_LibName}-Test-${__NAME}" PRIVATE ${ARGN} ${prm_LibName})
			add_test(NAME "${prm_LibName}-Test-${__NAME}" COMMAND "${prm_LibName}-Test-${__NAME}")
			ae2f_UltraError(${prm_LibName}-Test-${__NAME} PRIVATE ${prm_LibName}-Test-${__NAME})
		endforeach()
	endif()
endfunction()

# @brief
# Makes a Library installable. \n
# Configuration file could be selected here
# 
# @param prm_TarName
# Library name you want.
# 
# @param prm_TarPrefix
# [STATIC | SHARED | INTERFACE]
# 
# @param prm_includeDir
# The include directory relative to the project CMakeLists.txt
# 
# @param prm_namespace
# Namespace (or header root directory after include)
# 
# @param prm_configpath
# The path where the input file for Configuration lies.
# 
# @param ...
# The sources for the project.
function(ae2f_CoreLibTentConfigCustom prm_TarName prm_TarPreFix prm_includeDir prm_namespace prm_configpath)
	# Namespace Package
	include(GNUInstallDirs)

	include_directories(${prm_includeDir})
	add_library(${prm_namespace}-${prm_TarName} ${prm_TarPreFix} ${ARGN})
	add_library(${prm_namespace}::${prm_TarName} ALIAS ${prm_namespace}-${prm_TarName})

	if(${ae2f_nakedalais})
		add_library(${prm_TarName} ALIAS ${prm_namespace}-${prm_TarName})
	endif()

	target_include_directories(
		${prm_namespace}-${prm_TarName} INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${prm_includeDir}/>  
		$<INSTALL_INTERFACE:${prm_includeDir}/${prm_namespace}/>
		)

	# Install Settings
	install(TARGETS ${prm_namespace}-${prm_TarName}
		EXPORT ${prm_namespace}-${prm_TarName}Targets
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

	install(DIRECTORY ${prm_includeDir}/${prm_namespace}
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${prm_namespace}
		)

	# Package
	install(EXPORT ${prm_namespace}-${prm_TarName}Targets
		FILE ${prm_namespace}-${prm_TarName}Targets.cmake
		NAMESPACE ae2f::
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
		)

	# Pack Conf
	include(CMakePackageConfigHelpers)
	configure_package_config_file(
		${prm_configpath}
		${CMAKE_CURRENT_BINARY_DIR}/${prm_namespace}-${prm_TarName}Config.cmake
		INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
		)

	install(FILES
		${CMAKE_CURRENT_BINARY_DIR}/${prm_namespace}-${prm_TarName}Config.cmake
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
		)

	set(${prm_namespace}__${prm_TarName}__TENT ${prm_namespace}-${prm_TarName} CACHE STRING ${prm_namespace}-${prm_TarName})
endfunction()

# @brief
# Makes a Library installable.
# 
# @param prm_TarName
# Library name you want.
# 
# @param prm_TarPrefix
# [STATIC | SHARED | INTERFACE]
# 
# @param prm_includeDir
# The include directory relative to the project CMakeLists.txt
# 
# @param prm_namespace
# Namespace (or header root directory after include)
# 
# @param ...
# The sources for the project.
function(ae2f_CoreLibTent prm_TarName prm_TarPreFix prm_includeDir prm_namespace)
	ae2f_CoreLibTentConfigCustom(
		${prm_TarName} 
		${prm_TarPreFix} 
		${prm_includeDir} 
		${prm_namespace} 
		${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
		${ARGN}
		)
endfunction()

# @brief
# Generate an interface project for document code for cmake utility functions. \n
# Available when ___DOC_CMAKE::ae2f_DOC is ON.
# 
# @param prm_TarName
# Library name you want.
# 
# @param prm_includeDir
# Where the documents exist
# The include directory relative to the project CMakeLists.txt
# 
# @param prm_namespace
# Namespace (or header root directory after include)
# 
# @param ...
# The past documents name
# @see ___DOC_CMAKE::ae2f_CoreLibTent
# @see ___DOC_CMAKE::ae2f_DOC
function(ae2f_CoreUtilityDocTent prm_TarName prm_includeDir prm_namespace)
	if(ae2f_DOC)
		file(GLOB_RECURSE src ${prm_includeDir} "*.cmake.hpp")
		ae2f_CoreLibTent(${prm_TarName}-CMakeDoc INTERFACE ${prm_includeDir} ${prm_namespace}doc ${src})
		foreach(lib ${ARGN})
			target_link_libraries(${prm_TarName}-CMakeDoc INTERFACE ${lib}-CMakeDoc)
		endforeach()
	endif()
endfunction()

# Domain name customization.
function(ae2f_CoreLibFetch_DNS prm_AuthorName prm_namespace prm_TarName prm_TagName prm_Domain)
	if(NOT TARGET ${prm_namespace}::${prm_TarName})
		if(NOT EXISTS ${ae2f_ProjRoot}/${ae2f_submod}/${prm_AuthorName}/${prm_TarName}/CMakeLists.txt)
			execute_process(
				COMMAND 
				git clone 
				https://${prm_Domain}/${prm_AuthorName}/${prm_TarName} 
				${ae2f_ProjRoot}/${ae2f_submod}/${prm_AuthorName}/${prm_TarName}
				--branch ${prm_TagName} ${ARGN}
				RESULT_VARIABLE result
				)

			if(result)
				message(FATAL_ERROR "Fetching ${prm_AuthorName}/${prm_TarName} from Github Failed.")
			endif()
		endif()

		if(NOT ${prm_AuthorName}__${prm_namespace}__${prm_TarName}__SUB)
			set(${prm_AuthorName}__${prm_namespace}__${prm_TarName}__SUB ON)
			add_subdirectory(
				${ae2f_ProjRoot}/${ae2f_submod}/${prm_AuthorName}/${prm_TarName}
				${ae2f_BinRoot}/${ae2f_submod}/${prm_AuthorName}/${prm_TarName}
				)
		endif()
	endif()

	set(
		${prm_AuthorName}__${prm_namespace}__${prm_TarName}__FETCHED 
		${prm_namespace}::${prm_TarName} CACHE STRING ${prm_namespace}::${prm_TarName}
		)

endfunction()

# @brief 
# Domain name will stick on github.
# 
# It will try to fetch the cmake project ae2f-Core like project for Local and Github. \n
# @see ___DOC_CMAKE::ae2f_LibDirGlob is the given path to check. \n 
# 
# Once the project is in given directory, it will not try to fetch it from internet.
# 
# Fetched library will be in ${prm_AuthorName}__${prm_namespace}__${prm_TarName}__FETCHED 
# 
# @param prm_AuthorName 
# Author name
# @param prm_TarName
# Target name 
# @param prm_TagName
# Tag name
function(ae2f_CoreLibFetch_NS prm_AuthorName prm_namespace prm_TarName prm_TagName)
	ae2f_CoreLibFetch_DNS(
		${prm_AuthorName} 
		${prm_namespace} 
		${prm_TarName} 
		${prm_TagName} 
		"github.com" 
		${ARGN}
		)
endfunction()


# Deprecated. works only when Authorname and namespace are same.
function(ae2f_CoreLibFetch prm_AuthorName prm_TarName prm_TagName)
	ae2f_CoreLibFetch_NS(${prm_AuthorName} ${prm_AuthorName} ${prm_TarName} ${prm_TagName})

	set(
		${prm_AuthorName}__${prm_TarName}__FETCHED
		${${prm_AuthorName}__${prm_AuthorName}__${prm_TarName}__FETCHED}
		CACHE STRING
		${${prm_AuthorName}__${prm_AuthorName}__${prm_TarName}__FETCHED}
		)
endfunction()


# Fetched library will be in ${prm_AuthorName}__${prm_namespace}__${prm_TarName}__FETCHED 
function(ae2f_CoreLibFetchX_NS prm_AuthorName prm_namespace prm_TarName prm_TagName)
	find_package(${prm_TarName})

	if(${prm_TarName}_FOUND)
		set(
			${prm_AuthorName}__${prm_namespace}__${prm_TarName}__FETCHED
			${prm_namespace}::${prm_TarName} CACHE STRING ${prm_namespace}::${prm_TarName}
			)
	else()
		ae2f_CoreLibFetch_NS(${prm_AuthorName} ${prm_namespace} ${prm_TarName} ${prm_TagName})
	endif()
endfunction()

# Deprecated, works when Authoranme and namespace are same.
function(ae2f_CoreLibFetchX prm_AuthorName prm_TarName prm_TagName)
	ae2f_CoreLibFetchX_NS(${prm_AuthorName} ${prm_AuthorName} ${prm_TarName} ${prm_TagName})

	set(
		${prm_AuthorName}__${prm_TarName}__FETCHED
		${${prm_AuthorName}__${prm_AuthorName}__${prm_TarName}__FETCHED}
		CACHE STRING
		${${prm_AuthorName}__${prm_AuthorName}__${prm_TarName}__FETCHED}
		)
endfunction()
