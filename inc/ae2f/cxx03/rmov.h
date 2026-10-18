#ifndef	ae2f_cxx_rmov_h
#define ae2f_cxx_rmov_h

#include <ae2f/LangVer.h>

#if	ae2f_stdcc_v >= 201100L
#	include <utility>
#	define	ae2f_rty(ty)	ty&&
#	define	ae2f_rmov(c)	std::move(c)
#else
#	define	ae2f_rty(ty)	ty
#	define	ae2f_rmov(c)	(c)
#endif

#endif
