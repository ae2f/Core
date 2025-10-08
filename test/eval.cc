#include "ae2f/Cast.h"
#include <ae2f/Call.h>
#include <stdio.h>

ae2f_evaldef(
		template<int a>, <a>
		, ae2f_constextendedeval, ae2f_constextendedfun
		, int, Hello, _Hello, char v, v) 
{ return v + a; }

/*
 * ae2f_evaldef(tmpldef, tmpluse, keyeval, keyexpr, ret_t, nameeval, nameexpr, prmdef, prmuse)
 */

int main() {
	int a = _Hello<0>(2);
	int* ae2f_restrict v = 0;
	printf("%d\n", a);
	return 0;
}
