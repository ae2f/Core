#if !defined(ae2f_errGlobal)
// Those numbers with [ae2f_errint_t] will be the state.
#define ae2f_errGlobal

#include "Cast.h"

// Informs that this number represents the error.
typedef int ae2f_errint_t;

// The Operation you've wanted has beed succeed. 
#define ae2f_errGlobal_OK ae2f_static_cast(ae2f_errint_t, 0)

// Failed to find the function on preprocessor which is callable for some reason
// No operation has beed done.
#define ae2f_errGlobal_IMP_NOT_FOUND ae2f_static_cast(ae2f_errint_t, 1)

// Failed to refer the pointer either l-value inside the function.
#define ae2f_errGlobal_PTR_IS_NULL ae2f_static_cast(ae2f_errint_t, 2)

// Failed freeing the memory.
#define ae2f_errGlobal_FLUSH_FAILED ae2f_static_cast(ae2f_errint_t, 3)

// stdlib allocating functions (malloc, calloc, realloc) has been failed.
#define ae2f_errGlobal_ALLOC_FAILED ae2f_static_cast(ae2f_errint_t, 4)

// Found that operation is invalid inside the function.
// The operation may have been ceased while the middle.
#define ae2f_errGlobal_WRONG_OPERATION ae2f_static_cast(ae2f_errint_t, 5)

// Does not mean a thing.
// Just a Largest value of [ae2f_errGlobal] field.
#define ae2f_errGlobal_LMT ae2f_static_cast(ae2f_errint_t, 6)

#endif // defined(ae2f_errGlobal)