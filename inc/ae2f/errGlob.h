/**
 * @file errGlob.h
 * @author ae2f
 * @brief 
 * Those numbers with [ @ref ae2f_err_t ] will be the state.
 * 
 * @date 2025-02-01
 * 
 * @copyright Copyright (c) 2025
 */

#if !defined(ae2f_errGlobal_h)
#define ae2f_errGlobal_h

#include "./c90/StdInt.h"

/** 
 * @typedef ae2f_err_t
 * @brief Least integer type to store the error value
 * @see ae2f_errGlob
 * */
typedef uint_least8_t ae2f_err_t;


/**
 * @enum ae2f_errGlob
 * */
typedef enum {
        /** @brief Success */
        ae2f_errGlob_OK = 0,

        /** @brief Implementation not found (not expected) */
        ae2f_errGlob_IMP_NOT_FOUND = 1,

        /** @brief Null Pointer Exception */
        ae2f_errGlob_PTR_IS_NULL = 2,

        /** @brief Releasing, flushing, etc has been failed. */
        ae2f_errGlob_FLUSH_FAILED = 4,

        /** @brief Allocation has failed. */
        ae2f_errGlob_ALLOC_FAILED = 8,

        /** @brief Wrong Ooperation */
        ae2f_errGlob_WRONG_OPERATION = 16,

        /** @brief Error for another reason, such as low level. (See another status value.) */
        ae2f_errGlob_NFOUND = 32,

        /** @brief Operation has finished. */
        ae2f_errGlob_DONE_HOWEV = 64,
        ae2f_errGlob_
} ae2f_errGlob;



/** 
 * @deprecated
 *
 * @brief
 * Check if the state code is a critical error.
 * @param n {ae2f_err_t} Error code
 * @return If it is not zero, it is a critical error.
 */
#define ae2f_errGlobNormalised(n) (((n) & ae2f_errGlob_DONE_HOWEV) ? ae2f_errGlob_OK : (n))

#endif
