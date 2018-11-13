#include <stdio.h>
#include "vnrdef.h"
#include "nrdef.h"
#include "vnrutil.h"
#include "nrutil.h"
#include "simd_macro.h"
#include "morpho.h"
#include "mouvement.h"
#include "test_mouvement.h"
#include "test_morpho.h"
#include "test_mouvement_sse.h"

int main(){
	sd_routine_sse();
	return 0;
}
