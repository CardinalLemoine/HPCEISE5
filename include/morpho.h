#pragma once

#include <stdio.h>
#include "nrdef.h"
#include "nrutil.h"
#include <string.h>

#define EDGE 2

uint8** erosion(uint8 **frame, long nrl,long nrh,long ncl, long nch);
uint8** dilatation(uint8 **frame, long nrl,long nrh,long ncl, long nch);
uint8** ouverture(uint8 **frame, long nrl,long nrh,long ncl, long nch);
uint8** fermeture(uint8 **frame, long nrl,long nrh,long ncl, long nch);
