#ifndef ae2fc90_string_memcpy_h
#define ae2fc90_string_memcpy_h

#include <ae2f/cc/profiles.h>

#if	_ae2f_gnuc(!)0 || _ae2f_clang(!)0
#	define	ae2f_memcpy __builtin_memcpy
#else

#include <ae2f/Cast.h>
#include <ae2f/c90/stddef/size_t.h>

void*	ae2f_memcpy(void* ae2f_restrict r, const void* ae2f_restrict rd, ae2f_size_t c_bytenum) {
	const char* ae2f_restrict ae2f_mcpy_rd = ae2f_reinterpret_cast(const char* ae2f_restrict, rd);
	char* ae2f_restrict ae2f_mcpy_r = ae2f_reinterpret_cast(char* ae2f_restrict, r);

	while(c_bytenum--) {
		*ae2f_mcpy_r++ = *ae2f_mcpy_rd++;
	}

	return r;
}

#endif


#endif
