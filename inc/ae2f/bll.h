/**
 * @file bll.h
 * @brief	[B]ranch[l]ess [l]ogic
 *
 * @details
 * `uint` must be unsigned integer.  
 * `c_bool` must be 0/1   
 * `c_mask` must be all set or all not set (0, uint_max)  
 * `c_uint_btwidth` is the bit width of `uint`  
 * */

#ifndef	ae2f_bll_h
#define ae2f_bll_h

#include <ae2f/Cast.h>

#define	ae2f_bll_zero(uint)	ae2f_static_cast(uint, 0u)
#define	ae2f_bll_set(uint)	(~ae2f_bll_zero(uint))

#define	ae2f_bll_from_bool2(uint, c_bool)	\
	(ae2f_bll_zero(uint) - ae2f_static_cast(uint, c_bool))

#define	ae2f_bll_from_bool1(uint, c_bool)	\
	((uint)(((1u) << ((sizeof(uint) << 3) - (1))) | ((c_bool) << ((sizeof(uint) << 3)))))

#define	ae2f_bll_from_bool_naive2(uint, c_bool)	\
	ae2f_bll_from_bool2(uint, !!(c_bool))

#define	ae2f_bll_from_bool_naive1(uint, c_bool)	\
	ae2f_bll_from_bool1(uint, !!(c_bool))

/**
 * @brief ((c_mask) ? (c_tval) : (c_fval))
 * */
#define	ae2f_bll_sel(uint, c_mask, c_tval, c_fval)	\
	(((c_mask) & (c_tval)) | ((~(c_mask)) & (c_fval)))

#define	ae2f_bll_sel_bool1(uint, c_bool, c_tval, c_fval)	\
	ae2f_bll_sel(uint, ae2f_bll_from_bool1(uint, c_bool), c_tval, c_fval)

#define	ae2f_bll_sel_bool2(uint, c_bool, c_tval, c_fval)	\
	ae2f_bll_sel(uint, ae2f_bll_from_bool2(uint, c_bool), c_tval, c_fval)

#define	ae2f_bll_sel_bool_naive1(uint, c_bool, c_tval, c_fval)	\
	ae2f_bll_sel_bool1(uint, !!(c_bool), c_tval, c_fval)

#define	ae2f_bll_sel_bool_naive2(uint, c_bool, c_tval, c_fval)	\
	ae2f_bll_sel_bool2(uint, !!(c_bool), c_tval, c_fval)

#include <ae2f/c90/StdInt.h>

#define	ae2f_bll_sel_ptr(ptr_t, c_mask, c_tval, c_fval)	\
	ae2f_reinterpret_cast(	\
			ptr_t	\
			, ae2f_bll_sel(uptr, c_mask, ae2f_reinterpret_cast(uptr, c_tval), ae2f_reinterpret_cast(uptr, c_fval))	\
			)

#define	ae2f_bll_sel_ptrbool1(elm_t, c_bool, c_tval, c_fval)	\
	ae2f_bll_sel_ptr(elm_t, ae2f_bll_from_bool1(uptr, c_bool), c_tval, c_fval)

#define	ae2f_bll_sel_ptrbool_naive1(elm_t, c_bool, c_tval, c_fval)	\
	ae2f_bll_sel_ptrbool1(elm_t, !!(c_bool), c_tval, c_fval)

#endif
