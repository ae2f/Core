/**
 * @file Cast.h
 * @author ae2f
 * @brief
 * @date 2025-02-01
 *
 * @copyright Copyright (c) 2025
 *
 */

#if !defined(ae2f_Cast_h)

#define ae2f_Cast_h

#include <ae2f/LangVer.h>

#if	ae2f_stdcc_v
/* cppcheck-suppress misra-c2012-20.7 */
#define	ae2f_static_cast(t, v)		(static_cast<t>(v))
/* cppcheck-suppress misra-c2012-20.7 */
#define	ae2f_dynamic_cast(t, v)		(dynamic_cast<t>(v))
/* cppcheck-suppress misra-c2012-20.7 */
#define	ae2f_reinterpret_cast(t, v)	(reinterpret_cast<t>(v))
/* cppcheck-suppress misra-c2012-20.7 */
#define	ae2f_const_cast(t, v)		(const_cast<t>(v))
#else
#define	ae2f_static_cast(t, v)		((t)(v))
#define	ae2f_dynamic_cast(t, v)		((t)(v))
#define	ae2f_reinterpret_cast(t, v)	((t)(v))
#define	ae2f_const_cast(t, v)		((t)(v))
#endif

#endif
