/**
 * @file Call.h
 * @author ae2f
 * @brief 
 * @date 2025-02-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#define ON 1
#define OFF 0

#include "./Call.auto.h"

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
#if ae2f_IS_SHARED

#if ae2f_IS_WIN == ae2f_IS_LINUX
#pragma message("[WARNING] Platform not specified") 
#endif

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
