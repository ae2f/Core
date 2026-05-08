/** 
 * @file	profiles.h 
 * @brief	No header guard is required
 * */

/**
 * @def _ae2f_gnuc
 * @brief Available when compiled with gnu compiler.
 * */

#ifndef	_ae2f_gnuc
#	if	defined(__GNUC__)
#		define _ae2f_gnuc(a)	a
#	else
#		define _ae2f_gnuc(a)
#	endif
#endif

/**
 * @def N_ae2f_gnuc
 * @brief Available when not compiled with gnu compiler.
 */
#ifndef	N_ae2f_gnuc
#	if	defined(__GNUC__)
#		define N_ae2f_gnuc(a)
#	else
#		define N_ae2f_gnuc(a)	a
#	endif
#endif

#ifndef	_ae2f_clang
#	if	defined(__clang__)
#		define	_ae2f_clang(a)	a
#	else
#		define	_ae2f_clang(a)
#	endif
#endif

#ifndef	N_ae2f_clang
#	if	defined(__clang__)
#		define	N_ae2f_clang(a)
#	else
#		define	N_ae2f_clang(a)	a
#	endif
#endif

#ifndef	_ae2f_gcc
#	if	_ae2f_clang(!)1 && _ae2f_gnuc(!)0
#		define	_ae2f_gcc(a)	a
#	else
#		define	_ae2f_gcc(a)
#	endif
#endif

#ifndef	N_ae2f_gcc
#	if	_ae2f_clang(!)1 && _ae2f_gnuc(!)0
#		define	N_ae2f_gcc(a)	a
#	else
#		define	N_ae2f_gcc(a)
#	endif
#endif


/**
 * @def _ae2f_msvc
 * @brief Available when compiled with msvc.
 *
 * */
#ifndef	_ae2f_msvc
#	if	defined(_MSC_VER)
#		define	_ae2f_msvc(a)	a
#	else
#		define	_ae2f_msvc(a)
#	endif
#endif

/**
 * @def N_ae2f_msvc
 * @brief Available when not compiled with msvc.
 * */
#ifndef	N_ae2f_msvc
#	if	defined(_MSC_VER)
#		define	N_ae2f_msvc(a)
#	else
#		define	N_ae2f_msvc(a)	a
#	endif
#endif
