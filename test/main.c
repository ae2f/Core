#include <ae2f/Cmp.h>

#include <ae2f/Float.h>
#include <ae2f/Cast.h>
#include <ae2f/Keys.h>

#include <ae2f/errGlob.h>
#include <stdio.h>

#include <ae2f/Pack/Beg.h>
#include <ae2f/Pack/End.h>

#include <ae2f/Pack/Num.auto.h>

ae2f_structdef_v(struct, a, b, c, d) {
	int a;
};

ae2f_structdef_n(union, t, q) { int a; };
ae2f_structdef(union, qq) { int a; };

int main(void) {
	b v;
	t _v;

	void* ae2f_restrict hello = NULL;
	v.a = 1;
	_v.a = 2;

	printf("%d %d %d %p\n", ae2f_PackCount, v.a, _v.a, hello);
	return 0;
}
