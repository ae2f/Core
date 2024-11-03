#if !defined(ae2f_errGlobal)
// Those numbers with [ae2f_errint_t] will be the state.
#define ae2f_errGlobal

#include "Cast.h"
#include <stdint.h>

/// @brief
/// Informs that this number represents the error.
typedef uint8_t ae2f_errint_t;

/// @brief
/// The Operation you've wanted has beed succeed. 
#define ae2f_errGlob_OK ae2f_static_cast(ae2f_errint_t, 0)

/// @brief
/// Failed to find the function on preprocessor which is callable for some reason
/// No operation has beed done.
#define ae2f_errGlob_IMP_NOT_FOUND ae2f_static_cast(ae2f_errint_t, 0b1)

/// @brief
/// Failed to refer the pointer either l-value inside the function.
#define ae2f_errGlob_PTR_IS_NULL ae2f_static_cast(ae2f_errint_t, 0b10)

/// @brief
/// Failed freeing the memory.
#define ae2f_errGlob_FLUSH_FAILED ae2f_static_cast(ae2f_errint_t, 0b100)

/// @brief
/// stdlib allocating functions (malloc, calloc, realloc) has been failed.
#define ae2f_errGlob_ALLOC_FAILED ae2f_static_cast(ae2f_errint_t, 0b1000)

/// @brief
/// Found that parameter sent by programmer is invalid.
/// The operation may have been ceased while the middle.
#define ae2f_errGlob_WRONG_OPERATION ae2f_static_cast(ae2f_errint_t, 0b10000)

/// @brief
/// Found some errors, but not by parameters.
/// The operation has failed.
#define ae2f_errGlob_NFOUND ae2f_static_cast(ae2f_errint_t, 0b100000)

/// @brief
/// The operation went done.
/// Note that operation may not be valid.
#define ae2f_errGlob_DONE_HOWEV ae2f_static_cast(ae2f_errint_t, 0b1000000)

/// @brief
/// # For C++ Deconstructors
/// 
/// When the end of the lifecycle for C++ objects builtins, the error code will stored here.
ae2f_extern ae2f_errint_t ae2f_errGlob_LastErr;

#endif