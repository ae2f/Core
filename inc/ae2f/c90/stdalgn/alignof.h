#ifndef	ae2f_c90_stdalgn_alignof_h
#define	ae2f_c90_stdalgn_alignof_h

#include <ae2f/LangVer.h>

#if	ae2f_stdc_v < 201100L

#include <ae2f/c90/stddef/size_t.h>
#include <ae2f/Cast.h>

#define ae2f_alignof(ty)	ae2f_offsetof(struct { char c; ty m_mem; }, m_mem)

#else

#define	ae2f_alignof(ty)	_Alignof(ty)

#endif

#endif
