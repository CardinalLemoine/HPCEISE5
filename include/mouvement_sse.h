#pragma once

#include <stdio.h>
#include "nrdef.h"
#include "nrutil.h"
#include "vnrdef.h"
#include "vnrutil.h"
#include <string.h>
#include "mouvement.h"

#define EDGE_SSE 16

uint8** frame_difference_sse(uint8 **frame1, uint8 **frame2,long nrl,long nrh,long ncl, long nch);
uint8** sigma_delta_sse (uint8 **I, uint8 **M_1, uint8 **V_1, long nrl, long nrh, long ncl, long nch);



