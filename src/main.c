#include <stdio.h>
#include "vnrdef.h"
#include "nrdef.h"
#include "vnrutil.h"
#include "nrutil.h"
#include "simd_macro.h"
#include "morpho.h"
#include "mouvement.h"
#include "test_mouvement_sse.h"
#include "test_mouvement.h"
#include "test_morpho.h"
#include "test_morpho_sse.h"
#include <time.h>

int main(){
	clock_t t = clock();
	for(int i=0; i<1000; i++)
		test_morpho();
	t = clock() -t;
	printf("Time 1000 * MORPHO WITHOUT SSE: %.3f\n\n", 1.0*t/CLOCKS_PER_SEC);

	t = clock();
	for(int i=0; i<1000; i++)
		test_morpho_sse();
	t = clock() -t;
	printf("Time 1000 * MORPHO WITH SSE: %.3f\n\n", 1.0*t/CLOCKS_PER_SEC);

	fd_routine();
	t = clock()-t;
	printf("Time FD WITHOUT SSE: %.3f\n\n", 1.0*t/CLOCKS_PER_SEC);
	fd_routine_sse();
	t = clock()-t;
	printf("Time FD WITH SSE: %.3f\n\n", 1.0*t/CLOCKS_PER_SEC);
	sd_routine();
	t = clock()-t;
	printf("Time SD WITHOUT SSE: %.3f\n\n", 1.0*t/CLOCKS_PER_SEC);
	sd_routine_sse();
	t = clock()-t;
	printf("Time SD WITH SSE: %.3f\n\n", 1.0*t/CLOCKS_PER_SEC);
	return 0;

}
