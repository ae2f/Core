#define OFF false
#define ON true
#define CACHE constexpr
#define STRING const char*
#define option constexpr bool

/// @namespace ___DOC_CMAKE
/// @brief
/// Note they functions defined on CMake, not C/C++.
namespace ___DOC_CMAKE {
    /// @brief 
    /// When activated, it would generate project with the deaders of cmake utility functions.
    /// 
    /// Default value is ON.
    option ae2f_DOC = ON;

    /// @brief
    /// Activating this flag will cause all libraries built as shared libraries.
    option ae2f_IS_SHARED = OFF;

    /// @brief When activated, it would generate test projects
    option ae2f_TEST = ON;

    /// @brief Pre-defined library prefix.
    /// @warning Note that value is auto-generated.
    CACHE STRING ae2f_LIBPREFIX = ae2f_IS_SHARED ? "SHARED" : "STATIC";

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
    /// @param prm_namespace
    /// Namespace (or header root directory after include)
    /// 
    /// @param ...
    /// The sources for the project.
    constexpr void ae2f_CoreLibTent(
        auto prm_TarName, 
        auto prm_TarPreFix, 
        auto prm_includeDir, 
        auto prm_namespace, 
        ...
    );

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
    /// 
    /// @see ___DOC_CMAKE::ae2f_TEST
    constexpr void ae2f_CoreTestTent(
        auto prm_LibName, 
        auto prm_TestSourcesDir, 
        ...
    );

    /// @brief
    /// Generate an interface project for document code for cmake utility functions. \n
    /// Available when ___DOC_CMAKE::ae2f_DOC is ON.
    /// 
    /// @param prm_TarName
    /// Library name you want.
    /// 
    /// @param prm_includeDir
    /// Where the documents exist
    /// The include directory relative to the project CMakeLists.txt
    /// 
    /// @param prm_namespace
    /// Namespace (or header root directory after include)
    /// 
    /// @param ...
    /// The past documents name
    /// @see ___DOC_CMAKE::ae2f_CoreLibTent
    /// @see ___DOC_CMAKE::ae2f_DOC
    constexpr void ae2f_CoreUtilityDocTent(
        auto prm_TarName, 
        auto prm_includeDir, 
        auto prm_namespace,
        ...
    );
}