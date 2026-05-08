/**
 * @file cc.h
 * @brief Utility marks which could partially be available with gnu compiler.
 * @details Keys.h will utilise it to have keywords
 * */

#ifndef	ae2f_cc_h
#define ae2f_cc_h

#include "./LangVer.h"

#include "./cc/profiles.h"
#include "./cc/unless.h"
#include "./cc/callconv.h"
#include "./cc/inline.h"
#include "./cc/dylink.h"
#include "./cc/assume.h"
#include "./cc/fnpretty.h"
#include "./cc/switchctl.h"
#include "./cc/qualifier.h"

#include "./cc/expect/strict.h"
#include "./cc/expect/naive.h"

#include "./cc/branches/strict.h"
#include "./cc/branches/naive.h"

#define	ae2f_unexpected		ae2f_expected_not

#define	ae2f_expected_if	ae2f_ifneznrm
#define	ae2f_unexpected_but_if	ae2f_ifnezerr
#define	ae2f_unexpected_else	ae2f_ifeznrm
#define	ae2f_expected_but_else	ae2f_ifezerr

#define	ae2f_always_inline	ae2f_inline_f

#endif
