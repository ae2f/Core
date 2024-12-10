/// @file
/// Those numbers with [ @ref ae2f_err_t ] will be the state.

#if !defined(ae2f_errGlobal_h)
#define ae2f_errGlobal_h

#include <stdint.h>

/// @brief
/// Informs that this number represents the error.
typedef uint8_t ae2f_err_t;

/// @brief
/// The Operation you've wanted went successful. 
#define ae2f_errGlob_OK 0

/// @brief
/// Failed to find the function on preprocessor which is callable for some reason
/// No operation has beed done.
#define ae2f_errGlob_IMP_NOT_FOUND 0b1

/// @brief
/// Failed to refer the pointer either l-value inside the function.
#define ae2f_errGlob_PTR_IS_NULL 0b10

/// @brief
/// Failed freeing the memory.
#define ae2f_errGlob_FLUSH_FAILED 0b100

/// @brief
/// stdlib allocating functions (malloc, calloc, realloc) has been failed.
#define ae2f_errGlob_ALLOC_FAILED 0b1000

/// @brief
/// Found that parameter sent by programmer is invalid.
/// The operation may have been ceased while the middle.
#define ae2f_errGlob_WRONG_OPERATION 0b10000

/// @brief
/// Found some errors, but not by parameters.
/// The operation has failed.
#define ae2f_errGlob_NFOUND 0b100000

/// @brief
/// Means that error was not critical.
/// 
/// The operation went done. \n
/// Note that operation may not be valid.
#define ae2f_errGlob_DONE_HOWEV 0b1000000

/// @brief
/// Check if the state code is a critical error.
/// @param n {ae2f_err_t} Error code
/// @return If it is not zero, it is a critical error.
#define ae2f_errGlobNormalised(n) ((n & ae2f_errGlob_DONE_HOWEV) ? ae2f_errGlob_OK : n)

#endif