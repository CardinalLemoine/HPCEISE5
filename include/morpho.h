#pragma once

#include <stdio.h>
#include "nrdef.h"
#include "nrutil.h"
#include <string.h>
#include "mouvement.h"


uint8** erosion(uint8 **frame, long nrl,long nrh,long ncl, long nch);
uint8** dilatation(uint8 **frame, long nrl,long nrh,long ncl, long nch);
uint8** erosion_old(uint8 **frame, long nrl,long nrh,long ncl, long nch);
uint8** dilatation_old(uint8 **frame, long nrl,long nrh,long ncl, long nch);
uint8** ouverture(uint8 **frame, long nrl,long nrh,long ncl, long nch);
uint8** fermeture(uint8 **frame, long nrl,long nrh,long ncl, long nch);
uint8** ouverture_old(uint8 **frame, long nrl,long nrh,long ncl, long nch);
uint8** fermeture_old(uint8 **frame, long nrl,long nrh,long ncl, long nch);