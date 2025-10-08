/**
 * @file Call.h
 * @author ae2f
 * @brief 
 * @date 2025-02-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ae2f_Call_h
#define ae2f_Call_h

#include "./Platform.h"
#include "./Call.auto.h"

#if ae2f_IS_SHARED

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
#define ae2f_SHAREDCALL __declspec(dllimport)
#endif

#if ae2f_IS_LINUX || ae2f_IS_APPLE
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

#endif
