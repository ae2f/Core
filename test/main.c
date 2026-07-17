#include <ae2f/Cmp.h>

#include <ae2f/Float.h>
#include <ae2f/Cast.h>
#include <ae2f/Keys.h>

#include <ae2f/errGlob.h>
#include <stdio.h>

#include <ae2f/Pack/Beg.h>
#include <ae2f/Pack/End.h>

#include <ae2f/Cxx.h>


int main(void) {
	int* arr[3];
	int a = 10, b = 20, c = 30;
	arr[0] = &a;
	arr[1] = &b;
	arr[2] = &c;

	printf("%d\n", *arr[1]);


	return 0;
}
