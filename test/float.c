#include <stdio.h>
#include <ae2f/Float.h>

#define MAX_ERR 0.00001

uint64_t casttest() {
	ae2f_uFloat(double) src = { .m_float = -3.5f };
	ae2f_uFloat(float) dest = { .m_float = 23 };

	ae2f_FloatCast(
			dest.m_bits
			, true, 11, 52
			, 10

			, src.m_bits
			, true, 8, 23
			, 7

			, NULL
			);

	printf("GOT RESULT: %lf\n", dest.m_float);

	return 
		(src.m_float - dest.m_float) 
		* (src.m_float - dest.m_float) 
		
		> MAX_ERR;
}

int main() {
	uint64_t _res = 
		0
		| casttest()

		;

	printf("Huge test 0: %lu\n", _res);
	return _res;
}
