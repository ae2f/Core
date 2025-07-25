#include <ae2f/BitVec.h>

#include <ae2f/Call.h>

#include <ae2f/Cmp.h>

#include <ae2f/Float.h>
#include <ae2f/Cast.h>

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

int main() {
	b v;
	t _v;

	int* restrict hello = 0;

	printf("%d\n", ae2f_PackCount);
	return 0;
}
