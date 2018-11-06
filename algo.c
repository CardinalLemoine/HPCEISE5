#include <stdio.h>
#include "nrdef.h"
#include "nrutil.h"
#include <string.h>
#include <stdlib.h>

#define N 3
#define VMIN 1
#define VMAX 255

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

void sigma_delta (uint8 **I, uint8 **M, uint8 **M_1, uint8 **O, 
                    uint8 **V, uint8 **V_1, uint8 **E, long nrh, long nch)
{
    // step 1
    for (long i=0; i<nrh; i++)
    {
        for (long j=0; j<nch; j++)
        {
            if (M[i][j] < I[i][j])
                M[i][j] = M_1[i][j] + 1;
            else if (M[i][j] > I[i][j])
                M[i][j] = M_1[i][j] - 1;
            else
                M[i][j] = M_1[i][j];
        }
    }

    // step 2
    for (long i=0; i<nrh; i++)
    {
        for (long j=0; j<nch; j++)
        {
            O[i][j] = abs(M[i][j] - I[i][j]);
        }
    }

    // step 3
    for (long i=0; i<nrh; i++)
    {
        for (long j=0; j<nch; j++)
        {
            if (V[i][j] < N * O[i][j])
                V[i][j] = V_1[i][j] + 1;
            else if (V[i][j] > N * O[i][j])
                V[i][j] = V_1[i][j] - 1;
            else
                V[i][j] = V_1[i][j];
            V[i][j] = fmax(fmin(V[i][j], VMAX), VMIN);
        }
    }

    // step 4
    for (long i=0; i<nrh; i++)
    {
        for (long j=0; j<nch; j++)
        {
            if (O[i][j] < V[i][j])
                E[i][j] = 0;
            else
                E[i][j] = 1;
        }
    }
}
