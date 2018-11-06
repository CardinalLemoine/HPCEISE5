#include <stdio.h>
#include "nrdef.h"
#include "nrutil.h"
#include <string.h>
#include <stdlib.h>

uint8** frame_difference(uint8 **frame1, uint8 **frame2,long nrl,long nrh,long ncl, long nch){

	uint8 **f_diff = ui8matrix(nrl, nrh, ncl, nch);
	int seuil = 40;
	int diff;

	for(int i=0; i<=nrh; i++) {
	    for(int j=0; j<=nch; j++) {
		    diff = abs(frame2[i][j] - frame1[i][j]); //frame2 est a l'instant t, frame1 est à l'instant t-1
			if(diff < seuil){
				f_diff[i][j] = 0;			
			}
			else{
				f_diff[i][j] = 255;			
			}
    	}
	}
	
	return f_diff;
}
