#pragma once

#include <stdio.h>
#include "nrdef.h"
#include "nrutil.h"
#include "vnrdef.h"
#include "vnrutil.h"
#include <string.h>
#include "morpho.h"
#include "mouvement_sse.h"

uint8** dilatation_sse(uint8 **frame, long nrl,long nrh,long ncl, long nch);
uint8** erosion_sse(uint8 **frame, long nrl,long nrh,long ncl, long nch);
uint8** ouverture_sse(uint8 **frame, long nrl,long nrh,long ncl, long nch);
uint8** fermeture_sse(uint8 **frame, long nrl,long nrh,long ncl, long nch);

