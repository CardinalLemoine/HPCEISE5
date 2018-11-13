#include <stdio.h>
#include "nrdef.h"
#include "nrutil.h"
#include "morpho.h"
#include <string.h>
#include <stdlib.h>

/*******************************************************************
uint8** erosion()
Retourne une image qui contient l'image frame ayant subi une erosion
*******************************************************************/
uint8** erosion(uint8 **frame, long nrl,long nrh,long ncl, long nch){
	int i,j,k,l;
	uint8 **f_ero = ui8matrix(nrl-EDGE, nrh+EDGE, ncl-EDGE, nch+EDGE);
 	uint8 out;
    for(i=nrl; i<=nrh; i++){
    	for(j=ncl; j<=nch; j++){
            out = 255;
            for(k =-1;k <=1;k++){
                for(l = -1; l<= 1 ; l++){
                    out &= frame[i+k][j+l];
                }
            }
            f_ero[i][j] = out;
        }
    }
	return f_ero;
}

/*******************************************************************
uint8** dilatation()
Retourne une image qui contient l'image frame ayant subi une dilatation
*******************************************************************/
uint8** dilatation(uint8 **frame, long nrl,long nrh,long ncl, long nch){
	int i,j,k,l;
	uint8 **f_dil = ui8matrix(nrl-EDGE, nrh+EDGE, ncl-EDGE, nch+EDGE);
	uint8 out;
    for(i=nrl; i<=nrh; i++){
        for(j=ncl; j<=nch; j++){
            out = 0;
            for(k =-1;k <=1;k++){
                for(l = -1; l<= 1 ; l++){
                    out |= frame[i+k][j+l];
                }
            }
            f_dil[i][j] = out;
        }
    }
	return f_dil;
}

/*******************************************************************
uint8** ouverture()
Retourne une image qui contient l'image frame ayant subi une ouverture
Pour cela, le frame subit une erosion puis une dilatation
*******************************************************************/
uint8** ouverture(uint8 **frame, long nrl,long nrh,long ncl, long nch){
	uint8 **f_temp = erosion(frame, nrl, nrh, ncl, nch);
	uint8 **f_ouv = dilatation(f_temp,nrl,nrh,ncl,nch);
	free_ui8matrix(f_temp, nrl-EDGE, nrh+EDGE, ncl-EDGE, nch+EDGE);
	return f_ouv;
}

/*******************************************************************
uint8** fermeture()
Retourne une image qui contient l'image frame ayant subi une fermeture
Pour cela, le frame subit une dilatation puis une erosion
*******************************************************************/
uint8** fermeture(uint8 **frame, long nrl,long nrh,long ncl, long nch){
	uint8 **f_temp = dilatation(frame, nrl, nrh, ncl, nch);
	uint8 **f_fer = erosion(f_temp,nrl,nrh,ncl,nch);
	free_ui8matrix(f_temp, nrl-EDGE, nrh+EDGE, ncl-EDGE, nch+EDGE);
	return f_fer;
}
