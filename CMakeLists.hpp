/// @namespace ____ae2f_Core_Def_CMAKE
/// @brief
/// Note they functions defined on CMake, not C/C++.
namespace ____ae2f_Core_Def_CMAKE {
    constexpr bool OFF = 0, ON = 1;

    /// @brief
    /// Activating this flag will cause all libraries built as shared libraries.
    /// 
    /// Default value is OFF.
    constexpr bool ae2f_IS_SHARED = OFF;

    /// @brief
    /// Set the structure pack for pre-defined structures from interfaces.
    ///
    /// If it is set to zero, default structure pack will be preserved.
    ///
    /// Default value is 0.
    constexpr unsigned int ae2f_packcount = 0;

    /// @brief
    /// Pre-defined global float type. \n
    /// It is set to float as default.
    using ae2f_float = float;

    /// @brief
    /// Makes a Library installable.
    /// 
    /// @param prm_TarName
    /// Library name you want.
    /// 
    /// @param prm_TarPrefix
    /// [STATIC | SHARED | INTERFACE]
    /// 
    /// @param prm_includeDir
    /// The include directory relative to the project CMakeLists.txt
    /// 
    /// @param ...
    /// The sources for the project.
    constexpr void ae2f_CoreLibProjTent(auto prm_TarName, auto prm_TarPreFix, auto prm_includeDir, ...);

    /// @brief
    /// Iterates a directory `prm_TestSourcesDir` and 
    /// Make a test case for every source.
    /// 
    /// @param prm_LibName
    /// Base Library name
    /// 
    /// @param prm_TestSourcesDir
    /// A directory where the stand-alone test codes locate. \n
    /// Every sources under that directory must be stand-alone, which means it must not depends on another memory, function, etc.
    /// 
    /// @param ...
    /// Additional Libraries if you want
    constexpr void ae2f_CoreTestTent(auto prm_LibName, auto prm_TestSourcesDir, ...);
}