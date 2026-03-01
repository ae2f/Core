#include <ae2f/cc.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

const int GLOBAL_THREE = 3;

ae2f_inline static int ae2f_ccpure RETURN_THREE_CONST(void) {
	return 3;
}

ae2f_inline static int ae2f_ccpure RETURN_THREE_PURE(void) {
	return GLOBAL_THREE;
}

int ae2f_ccconst ae2f_noexcept I_ADD(const int, const int);

int ae2f_ccconst ae2f_noexcept I_ADD(const int a, const int b) {
	return a + b;
}

int main(void) {
	void* ae2f_restrict	HELLO;
	int  ae2f_unused	UNUSED;

	assert(I_ADD(3, 4) == 7);
	ae2f_assume_strict(3);
	{ ae2f_assume(RETURN_THREE_CONST()); }

	HELLO = malloc(3);
	assert(HELLO);
	{ ae2f_assume(HELLO); }
	free(HELLO);

	if(ae2f_expected(RETURN_THREE_PURE())) {
		puts("Hello World!");
	}

	if(ae2f_expected_not(I_ADD(3, -3))) {
		ae2f_unreachable();
		puts("hi");
	}

	return 0;
}
