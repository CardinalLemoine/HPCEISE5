#pragma once

#include <stdio.h>
#include "nrdef.h"
#include "nrutil.h"
#include "vnrdef.h"
#include "vnrutil.h"
#include <string.h>

#define FD_SEUIL 5
#define EDGE 2
#define N 2
#define VMIN 1
#define VMAX 255

uint8** frame_difference_sse(vuint8 **frame1, vuint8 **frame2,long nrl,long nrh,long ncl, long nch);
uint8** sigma_delta_sse (uint8 **I, uint8 **M_1, uint8 **V_1, long nrl, long nrh, long ncl, long nch);