#include <stdio.h>
#include "nrdef.h"
#include "nrutil.h"
#include <string.h>
#include "algo.h"

#define FRAME_COUNT 300

int  main() {
	
	long nrl = 0;
	long nrh = 0;
	long ncl = 0;
	long nch = 0;
	char filename[256];
	uint8 **sequence[FRAME_COUNT];
	uint8 **fd[FRAME_COUNT-1];
	
	//Chargement de tout les frames dans une liste
	for(int i=0;i<FRAME_COUNT;i++){
		sprintf(filename,"hall/hall%06d.pgm",i);
		sequence[i] = LoadPGM_ui8matrix(filename, &nrl, &nrh, &ncl, &nch);	
	}
	
	//Affichage d'une matrice
	display_ui8matrix(sequence[200],nrl,nrh,ncl,nch, "%ld","FRAME0");

	//Application de l'algo Frame Difference	
	for(int i=1;i<FRAME_COUNT;i++){
		fd[i-1] = frame_difference(sequence[i-1],sequence[i], nrl, nrh, ncl, nch);	
	}
	
	display_ui8matrix(fd[200],nrl,nrh,ncl,nch, "%ld","FRAME0");

	//Sauvegarde output frame difference
	for(int i=0;i<FRAME_COUNT-1;i++){
		sprintf(filename,"fd_hall/hall%06d.pgm",i);
 		SavePGM_ui8matrix(fd[i], nrl, nrh, ncl, nch, filename);
	}

	return 0;

}
