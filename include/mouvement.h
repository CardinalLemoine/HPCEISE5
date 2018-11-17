#pragma once

#include <stdio.h>
#include "nrdef.h"
#include "nrutil.h"
#include <string.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

#define N 2
#define VMIN 1
#define VMAX 254

#define FD_SEUIL 20
#define EDGE 2
#define FRAME_COUNT 300

uint8** frame_difference(uint8 **frame1, uint8 **frame2,long nrl,long nrh,long ncl, long nch);
uint8** sigma_delta (uint8 **I, uint8 **M, uint8 **V, long nrl, long nrh, long ncl, long nch);