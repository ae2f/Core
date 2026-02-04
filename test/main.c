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
	void* ae2f_restrict hello = ae2f_NIL;

	printf("%d %p\n", ae2f_PackCount, hello);
	return 0;
}
