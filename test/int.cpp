#include <ae2f/BInt.h>
#include <stdio.h>

int main() {
	constexpr size_t 
		a = 0
		, b = ae2f_BIntCmp0(&a, false, 64, 0);

	if(b) {
		puts("ae2f_BIntCmp0 Error");
		return 1;
	}

	constexpr int e = -31;
	constexpr char d = -125;

	constexpr size_t b2 = ae2f_BIntCmp<
		true, sizeof(int) << 3, 0
		, true, sizeof(char) << 3, 0
		>(&e, &d);

	if(b2 < 0) 
	{
		puts("ae2f_BIntCmp Error");
		return 1;
	}

	puts("So Far So Good");

	return 0;
}
