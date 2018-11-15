#pragma once

#include <stdio.h>
#include "nrdef.h"
#include "nrutil.h"
#include "morpho.h"
#include <string.h>

uint8** wrapping(uint8 **m,long nrl,long nrh,long ncl, long nch);
void test_morpho();
void test_morpho_old();
