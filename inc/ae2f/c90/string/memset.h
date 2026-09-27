
#ifndef	ae2fc90_string_memset
#define ae2fc90_string_memset
#include <ae2f/Cast.h>
#include <ae2f/cc/qualifier.h>
#include <ae2f/c90/stddef/size_t.h>

#	if	_ae2f_clang(!)0 || _ae2f_gcc(!)0 || _ae2f_gnuc(!)0
#		define	ae2f_memset(wr_dst, c_ch, c_bytenum)	\
	__builtin_memset(ae2f_reinterpret_cast(void* ae2f_restrict, wr_dst), ae2f_static_cast(int, c_ch), ae2f_static_cast(ae2f_size_t, c_bytenum))
#	else

#include <ae2f/cc/qualifier.h>

static void* ae2f_memset(void* ae2f_restrict wr_dst, int c, ae2f_size_t c_bytenum) {
	unsigned char* ae2f_restrict ae2fcc_memset_buf = ae2f_reinterpret_cast(unsigned char* ae2f_restrict, wr_dst);

	while(c_bytenum --> 0)
		*ae2fcc_memset_buf++ = ae2f_static_cast(unsigned char, c);

	return wr_dst;
}

#define	ae2f_memset ae2f_memset

#	endif
#endif
