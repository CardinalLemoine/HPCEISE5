#include <stdio.h>
#include "test_mouvement_sse.h"

void fd_routine_sse(){
	//Init vars scalaires
	int nrl = 0;
	int nrh = 0;
	int ncl = 0;
	int nch = 0;
	//Init vars vectoiels
	int vi0, vj0, vi1, vj1
;
	char filename[256]; //nom du fichier image dans /hall
	uint8 **sequence[FRAME_COUNT]; //L'ensemble des images de la sequence
	uint8 **fd[FRAME_COUNT-1]; //L'ensemble des images de la sequence apres FD

	//Chargement de tout les frames dans une liste
	printf("Loading PGM sequence...\n");
	for(int i=0;i<FRAME_COUNT;i++){
		sprintf(filename,"hall/hall%06d.pgm",i);
		sequence[i] = LoadPGM_ui8matrix(filename, &nrl, &nrh, &ncl, &nch);	
	}
}