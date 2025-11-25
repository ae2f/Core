/**
 * @file cc.h
 * @brief Utility marks which could partially be available with gnu compiler.
 * @details Keys.h will utilise it to have keywords
 * */
#include "./LangVer.h"

/**
 * @def _ae2f_gnuc(a)
 * @brief Available when compiled with gcc compiler.
 *
 * @def N_ae2f_gnuc(a)
 * @brief Available when not compiled with gnu compiler.
 * */
#if	defined(__GNUC__)
#define _ae2f_gnuc(a)	a
#define N_ae2f_gnuc(a)	
#else
#define _ae2f_gnuc(a)	
#define N_ae2f_gnuc(a)	a
#endif

/**
 * @def _ae2f_gnuc(a)
 * @brief Available when compiled with msvc.
 *
 * @def N_ae2f_gnuc(a)
 * @brief Available when not compiled with msvc.
 * */
#if	defined(_MSC_VER)
#define	_ae2f_msvc(a)	a
#define	N_ae2f_msvc(a)	
#else
#define _ae2f_msvc(a)
#define N_ae2f_msvc(a)	a
#endif

/** 
 * @def ae2f_ccpure
 * @brief Keyword as `[[pure]]` on C23.
 * */
#undef	ae2f_ccpure
#if	_ae2f_gnuc(!)0
#define ae2f_ccpure	__attribute__((pure))
#elif	__ae2f_stdcheck_C(202300L) && ae2f_stdcc_v
#define ae2f_ccpure	[[pure]]
#else
#define ae2f_ccpure
#endif


/** 
 * @def ae2f_ccconst
 * @brief Keyword as `[[const]]` on C23..
 * */
#if	_ae2f_gnuc(!)0
#define ae2f_ccconst	__attribute__((const))
#elif __ae2f_stdcheck_C(202300L) && ae2f_stdcc_v
#define ae2f_ccconst	[[const]]
#else
#define ae2f_ccconst
#endif

/** 
 * @def ae2f_restrict
 * @brief Keyword as `restrict` on C99.
 * */
#undef	ae2f_restrict
#if	_ae2f_gnuc(!)0
#define ae2f_restrict	__restrict
#elif	_ae2f_msvc(!)0
#define ae2f_restrict	__restrict
#elif	__ae2f_stdcheck_C(199900L) && ae2f_stdcc_v
#define ae2f_restrict	restrict
#else
#define ae2f_restrict
#endif

/**
 * @def ae2f_retnew
 * @brief The returning pointer does not alias to existing object.
 * */
#if	_ae2f_msvc(!)0
#define ae2f_retnew	__declspec(restrict)
#elif	_ae2f_gnuc(!)0
#define ae2f_retnew	__attribute__((malloc))
#else
#define ae2f_retnew
#endif

