#include <stdio.h>
#include "nrdef.h"
#include "nrutil.h"
#include "morpho.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*******************************************************************
uint8** erosion()
Retourne une image qui contient l'image frame ayant subi une erosion
*******************************************************************/
uint8** erosion(uint8 **frame, long nrl,long nrh,long ncl, long nch){
	int i,j,k,l;
	uint8 **f_ero = ui8matrix(nrl-EDGE, nrh+EDGE, ncl-EDGE, nch+EDGE);
	uint8 out; 
	uint8 e00 = frame[nrl-1][ncl-1];
	uint8 e01 = frame[nrl-1][ncl];
	uint8 e02 = frame[nrl-1][ncl+1];
	uint8 e10 = frame[nrl][ncl-1];
	uint8 e11 = frame[nrl][ncl];
	uint8 e12 = frame[nrl][ncl+1];
	uint8 e20 = frame[nrl+1][ncl-1];
	uint8 e21 = frame[nrl+1][ncl];
	uint8 e22 = frame[nrl+1][ncl+1];

	/*EtAPE 2 : Droulage de boucle*/
    for(i=nrl+1; i<=nrh; i++){
		/*Init scalaire*/
    	for(j=ncl; j<=nch; j++){
            out = 255;
            out = out & e00 & e01 & e02 & e10 & e11 & e12 & e20 & e21 & e22;
            f_ero[i][j] = out;

			/*On decale les indices*/
			e00 = e01;
			e01 = e02;	
			e02 = frame[i-1][j+2];
			e10 = e11;
			e11 = e12;	
			e12 = frame[i][j+2];
			e20 = e21;
			e21 = e22;	
			e22 = frame[i+1][j+2];
        }
		e00 = frame[i-1][ncl-1];
		e01 = frame[i-1][ncl];
		e02 = frame[i-1][ncl+1];
		e10 = frame[i][ncl-1];
		e11 = frame[i][ncl];
		e12 = frame[i][ncl+1];
		e20 = frame[i+1][ncl-1];
		e21 = frame[i+1][ncl];
		e22 = frame[i+1][ncl+1];

    }

	return f_ero;
}

uint8** erosion_old(uint8 **frame, long nrl,long nrh,long ncl, long nch){
	clock_t t = clock();
	int i,j,k,l;
	uint8 **f_ero = ui8matrix(nrl-EDGE, nrh+EDGE, ncl-EDGE, nch+EDGE);
 	uint8 out;
	int opt = 0;
    for(i=nrl; i<=nrh; i++){
    	for(j=ncl; j<=nch; j++){
            out = 255;
            for(k =-1;k <=1;k++){
                for(l = -1; l<= 1 ; l++){
                    out &= frame[i+k][j+l];
					opt +=1;
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
	uint8 e00 = frame[nrl-1][ncl-1];
	uint8 e01 = frame[nrl-1][ncl];
	uint8 e02 = frame[nrl-1][ncl+1];
	uint8 e10 = frame[nrl][ncl-1];
	uint8 e11 = frame[nrl][ncl];
	uint8 e12 = frame[nrl][ncl+1];
	uint8 e20 = frame[nrl+1][ncl-1];
	uint8 e21 = frame[nrl+1][ncl];
	uint8 e22 = frame[nrl+1][ncl+1];

	/*EtAPE 2 : Droulage de boucle*/
    for(i=nrl; i<=nrh; i++){
    	for(j=ncl; j<=nch; j++){
            out = 0;
            out = out | e00 | e01 | e02 | e10 | e11 | e12 | e20 | e21 | e22;
            f_dil[i][j] = out;

			/*On decale les indices*/
			e00 = e01;
			e01 = e02;	
			e02 = frame[i-1][j+2];
			e10 = e11;
			e11 = e12;	
			e12 = frame[i][j+2];
			e20 = e21;
			e21 = e22;	
			e22 = frame[i+1][j+2];
        }
		e00 = frame[i-1][ncl-1];
		e01 = frame[i-1][ncl];
		e02 = frame[i-1][ncl+1];
		e10 = frame[i][ncl-1];
		e11 = frame[i][ncl];
		e12 = frame[i][ncl+1];
		e20 = frame[i+1][ncl-1];
		e21 = frame[i+1][ncl];
		e22 = frame[i+1][ncl+1];
    }
	return f_dil;
}

uint8** dilatation_old(uint8 **frame, long nrl,long nrh,long ncl, long nch){
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

uint8** ouverture_old(uint8 **frame, long nrl,long nrh,long ncl, long nch){
	uint8 **f_temp = erosion_old(frame, nrl, nrh, ncl, nch);
	uint8 **f_ouv = dilatation_old(f_temp,nrl,nrh,ncl,nch);
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

uint8** fermeture_old(uint8 **frame, long nrl,long nrh,long ncl, long nch){
	uint8 **f_temp = dilatation_old(frame, nrl, nrh, ncl, nch);
	uint8 **f_fer = erosion_old(f_temp,nrl,nrh,ncl,nch);
	free_ui8matrix(f_temp, nrl-EDGE, nrh+EDGE, ncl-EDGE, nch+EDGE);
	return f_fer;
}