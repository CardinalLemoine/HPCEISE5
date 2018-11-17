#include <stdio.h>
#include "nrdef.h"
#include "nrutil.h"
#include "mouvement.h"
#include <string.h>
#include <stdlib.h>

uint8** frame_difference(uint8 **frame1, uint8 **frame2,long nrl,long nrh,long ncl, long nch){
	uint8 **f_diff = ui8matrix(nrl-EDGE, nrh+EDGE, ncl-EDGE, nch+EDGE);
	int diff;

	for(int i=nrl; i<=nrh; i++) {
	    for(int j=ncl; j<=nch; j++) {
		    diff = abs(frame2[i][j] - frame1[i][j]); //frame2 est a l'instant t, frame1 est à l'instant t-1
			if(diff < FD_SEUIL){
				f_diff[i][j] = 0;			
			}
			else{
				f_diff[i][j] = 255;			
			}
    	}
	}
	
	return f_diff;
}

uint8** sigma_delta(uint8 **I, uint8 **M, uint8 **V, long nrl, long nrh, long ncl, long nch)
{
    uint8 **O = ui8matrix(nrl-EDGE, nrh+EDGE, ncl-EDGE, nch+EDGE);
	uint8 **E = ui8matrix(nrl-EDGE, nrh+EDGE, ncl-EDGE, nch+EDGE);

    for(int i=nrl; i<=nrh; i++){
        for(int j=ncl; j<=nch; j++){
            // step 1
            if(M[i][j] < I[i][j]){
                
                M[i][j]++;
            }
            else if(M[i][j] > I[i][j]){
                M[i][j]--;
            }
 
            // step 2
            O[i][j] = abs(M[i][j] - I[i][j]);
  
            // step 3
            if(V[i][j] < N * O[i][j]){
                V[i][j]++;
            }
            else if(V[i][j] > N * O[i][j]){
                V[i][j]--;
            }
            V[i][j] = max(min(V[i][j], VMAX), VMIN);
  
            // step 4
            if (O[i][j] < V[i][j]){
                E[i][j] = 0;
            }
            else{
                E[i][j] = 255;
            }
        }
    }
	
    free_ui8matrix(O, nrl-EDGE, nrh+EDGE, ncl-EDGE, nch+EDGE);
	return E;
}