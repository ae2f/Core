#include <ae2f/Keys.h>
#include <ae2f/c90/stdint/shorten.h>
#include <ae2f/bll.h>
#include <stdio.h>

int main(void);
int main(void) {
	if(0u != ae2f_bll_zero(umax)) {
		return 1;
	}

	{
		umax		IDX = (sizeof(umax) << 3u);
		while(0 != IDX--) { unless(ae2f_bll_set(umax) & ((umax)1u << IDX))  {
			/* cppcheck-suppress misra-c2012-21.6 */
			(void)printf("2: %u\n", (unsigned)IDX);
			return 2;
		}}
	}

	if(0u != ae2f_bll_from_bool1(umax, 0)) {
		return 3;
	}

	unless(0u != ae2f_bll_from_bool1(umax, 1)) {
		return 4;
	}

	unless(0u != (ae2f_bll_sel_bool1(umax, 1, 3u, 2u) == 3u)) {
		return 5;
	}

	return 0;
}
