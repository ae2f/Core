#include "./profiles.h"

#ifndef	ae2fcc_memset
#include <ae2f/Cast.h>
#include <ae2f/cc/qualifier.h>
#	if	_ae2f_clang(!)0 || _ae2f_gcc(!)0 || _ae2f_gnuc(!)0
#		define	ae2fcc_memset(wr_dst, c_ch, c_bytenum)	\
	__builtin_memset(ae2f_reinterpret_cast(void* ae2f_restrict, wr_dst), ae2f_static_cast(int, c_ch), ae2f_static_cast(size_t, c_bytenum))
#	else
#	include <string.h>
#		define	ae2fcc_memset(wr_dst, c_ch, c_bytenum)	\
	memset(ae2f_reinterpret_cast(void* ae2f_restrict, wr_dst), ae2f_static_cast(int, c_ch), ae2f_static_cast(size_t, c_bytenum))
#	endif
#endif
