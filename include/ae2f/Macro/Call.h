#define ON 1
#define OFF 0

#if (defined(_WIN32) || defined(_WIN64))
#define ae2f_IS_WIN 1
#else 
#define ae2f_IS_WIN 0
#endif 

#if (defined(__linux__))
#define ae2f_IS_LINUX 1
#else 
#define ae2f_IS_LINUX 0
#endif

#include <assert.h>

static_assert(ae2f_IS_WIN != ae2f_IS_LINUX, "Fucked");

#if OFF

#if ae2f_IS_WIN
/// @brief
/// # For Windows
/// 
/// shared function imp
#define ae2f_SHAREDEXPORT __declspec(dllexport)

/// @brief
/// # For Windows
/// 
/// Function api call
#define ae2f_SHAREDCALL
#else
/// @brief
/// # For Linux, gcc based.
/// 
/// shared function imp
#define ae2f_SHAREDEXPORT __attribute__((visibility("default")))

/// @brief
/// # For Linux, gcc based.
///
/// Function api call
#define ae2f_SHAREDCALL
#endif
#else

/// @brief
/// # It is no shared library.
/// 
/// shared function imp
#define ae2f_SHAREDEXPORT
/// @brief 
/// # It is no shared library.
///
/// Function api call
#define ae2f_SHAREDCALL
#endif
