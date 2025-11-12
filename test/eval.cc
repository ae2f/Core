#include <ae2f/Keys.h>
#include <stdio.h>

ae2f_evaldef(
		template<int a>, <a>
		, ae2f_constextendedeval, ae2f_constextendedfun
		, int, Hello, _Hello, char v, v) 
{ return v + a; }

/*
 * ae2f_evaldef(tmpldef, tmpluse, keyeval, keyexpr, ret_t, nameeval, nameexpr, prmdef, prmuse)
 */

int main(void) {
	int a = _Hello<0>(2);
	void* ae2f_restrict v = ae2f_NIL;
	printf("%d, %p\n", a, v);
	return 0;
}
