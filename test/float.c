#include <stdio.h>
#include <ae2f/Float.h>

#define MAX_ERR 0.00001

uint64_t casttest() {
	float src = 3.5f;
	double dest = 23;

	ae2f_FloatCast(
			&dest
			, true
			, 11, 10, 52

			, &src
			, true
			, 8, 7, 23

			, NULL
			);

	printf("DEST: %lf\n", dest);
	printf("SRC: %lf\n", src);

	return 
		(src - dest) 
		* (src - dest) 
		
		> MAX_ERR;
}


uint64_t casttest2() {
	double src = 0.234211;
	float dest = 23;

	ae2f_FloatCast(
			&dest
			, true
			, 8, 7, 23

			, &src
			, true
			, 11, 10, 52

			, NULL
			);

	printf("DEST: %lf\n", dest);
	printf("SRC: %lf\n", src);

	return 
		((src - dest) 
		* (src - dest) 
		
		> MAX_ERR) << 1;
}

int main() {
	uint64_t _res = 
		0
		| casttest()
		| casttest2()
		;

	printf("Huge test 0: %lu\n", _res);
	return _res;
}
