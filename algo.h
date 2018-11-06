#pragma once

#include <stdio.h>
#include "nrdef.h"
#include "nrutil.h"
#include <string.h>
#include <stdint.h>

uint8** frame_difference(uint8 **frame1, uint8 **frame2,long nrl,long nrh,long ncl, long nch);
void sigma_delta (uint8 **i, uint8 **m, uint8 **m_1, uint8 **o, 
                    uint8 **v, uint8 **v_1, uint8 **e, long nrh, long nch);
