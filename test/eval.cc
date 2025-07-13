#include "ae2f/Cast.h"
#include <ae2f/Call.h>
#include <stdio.h>

ae2f_evaldef(
		template<int a>, <0>
		, consteval, constexprfun
		, int, Hello, _Hello, char v, v) 
{ return v; }

int main() {
	int a = _Hello<0>(2);
	printf("%d\n", a);
	return 0;
}
