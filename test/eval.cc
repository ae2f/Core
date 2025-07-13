#include "ae2f/Cast.h"
#include <ae2f/Call.h>

ae2f_evaldef(
		template<int a>, <0>
		, consteval, constexprfun
		, int, Hello, _Hello, char v, v) 
{ return v; }

int main() {
	_Hello<0>(2);
	return 0;
}
