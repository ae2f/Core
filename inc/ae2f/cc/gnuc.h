/** 
 * @file gnuc.h 
 * @brief 
 * Utility to detect GNU compiler collection with preprocessor.
 *
 * @details
 * It uses `__GNUC__` to detect whether this source is compiled with gnu c compiler.
 *
 * @def _ae2f_gnuc(a)
 * @brief Available when compiled with gcc-like.
 *
 * @def N_ae2f_gnuc(a)
 * @brief Available when compiled with non-gcc-like.
 * */
#ifndef ae2f_gnuc_h
#define ae2f_gnuc_h

#ifdef __GNUC__
#define _ae2f_gnuc(a)	a
#define N_ae2f_gnuc(a)	
#else
#define _ae2f_gnuc(a)	
#define N_ae2f_gnuc(a)	a
#endif

#endif
