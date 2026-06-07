#include <ae2f/Keys.h>
#include <ae2f/c90/stdint/shorten.h>
#include <ae2f/bll.h>
#include <stdio.h>

int main(void);
int main(void) {
	if(ae2f_bll_zero(umax)) return 1;

	{
		umax		IDX = (sizeof(umax) << 3u);
		while(IDX--)	unless(ae2f_bll_set(umax) & ((umax)1u << IDX))  {
			printf("2: %u\n", (unsigned)IDX);
			return 2;
		}
	}

	if(ae2f_bll_from_bool1(umax, 0))
		return 3;

	unless(ae2f_bll_from_bool1(umax, 1))
		return 4;

	unless(ae2f_bll_sel_bool1(umax, 1, 3u, 2u) == 3u)
		return 5;

	return 0;
}
