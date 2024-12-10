# @namespace ___DOC_CMAKE
# @brief
# Note they functions defined on CMake, not C/C++.

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
        file(GLOB_RECURSE files "${prm_TestSourcesDir}/*")
        list(LENGTH files list_length)
        
        math(EXPR adjusted_length "${list_length} - 1")

        foreach(i RANGE 0 ${adjusted_length})
            list(GET files ${i} item)
            add_executable("${prm_LibName}-Test${i}" ${item})
            target_link_libraries("${prm_LibName}-Test${i}" ${ARGN} ${prm_LibName})
            add_test(NAME "${prm_LibName}-Test${i}" COMMAND "${prm_LibName}-Test${i}")
        endforeach()
    endif()
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
    # Namespace Package
    include(GNUInstallDirs)

    include_directories(${prm_includeDir})
    add_library(${prm_TarName} ${prm_TarPreFix} ${ARGN})

    target_include_directories(
        ${prm_TarName} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${prm_includeDir}/>  
        $<INSTALL_INTERFACE:${prm_includeDir}/${prm_namespace}/>
    )

    # Install Settings
    install(TARGETS "${prm_TarName}"
        EXPORT ${prm_TarName}Targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
        
    install(DIRECTORY ${prm_includeDir}/${prm_namespace}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${prm_namespace}
    )

    # Package
    install(EXPORT ${prm_TarName}Targets
        FILE ${prm_TarName}Targets.cmake
        NAMESPACE ae2f::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
    )
        
    # Pack Conf
    include(CMakePackageConfigHelpers)
    configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/${prm_TarName}Config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
    )
        
    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${prm_TarName}Config.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
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
# Where the headers are.
# The include directory relative to the project CMakeLists.txt
# 
# @param prm_namespace
# Namespace (or header root directory after include)
# 
# @param ...
# The documents for the project.
# @see ___DOC_CMAKE::ae2f_CoreLibTent
# @see ___DOC_CMAKE::ae2f_DOC
function(ae2f_CoreUtilityDocTent prm_TarName prm_includeDir prm_namespace)
    if(ae2f_DOC)
        ae2f_CoreLibTent(${prm_TarName}-CmakeDoc INTERFACE ${prm_includeDir} ${prm_namespace}doc ${ARGN})
    endif()
endfunction()