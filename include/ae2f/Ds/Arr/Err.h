/// @file
/// Helper header for ae2f/Ds/Arr.h
/// @warning 
/// This file has lack of definitions.

/// @brief
/// # It is not a critical error.
///
/// Failed to find the wanted value. \n 
/// Your array might have not been sorted finely.
/// @return 
/// @ref ae2f_errGlob_NFOUND \n
/// @ref ae2f_errGlob_DONE_HOWEV
#define ae2f_ds_Arr_NOT_FOUND ae2f_static_cast(ae2f_errint_t, 0b1100000)