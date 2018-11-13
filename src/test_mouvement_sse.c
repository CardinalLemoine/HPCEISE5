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

void sd_routine_sse(){
	long nrl = 0;
	long nrh = 0;
	long ncl = 0;
	long nch = 0;
	uint8 **sequence[FRAME_COUNT];
	uint8 **sd[FRAME_COUNT-1]; //L'ensemble des images de la sequence apres SD
	uint8 **sd_morpho[FRAME_COUNT-1];
	char filename[256];

	//Chargement de tout les frames dans une liste
	printf("Loading PGM sequence...\n");
	for(int i=0;i<FRAME_COUNT;i++){
		sprintf(filename,"hall/hall%06d.pgm",i);
		sequence[i] = LoadPGM_ui8matrix(filename, &nrl, &nrh, &ncl, &nch);	
	}
	
	//Application de l'algo Sigma Delta
	printf("Applying SD Algorithm...\n");
	uint8 **m = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **o = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **v = ui8matrix(nrl, nrh, ncl, nch);

	for(int i=nrl; i<nrh; i++)
	{
		for(int j=ncl; j<nch; j++)
		{
			m[i][j] = sequence[0][i][j];
			v[i][j] = VMIN;
		}
	}

	for(long i=1; i<FRAME_COUNT; i++)
		sd[i-1] = sigma_delta_sse(sequence[i], m, v, nrl, nrh, ncl, nch);

	//Sauvegarde output frame difference
	printf("Saving SD sequence...\n");
	for(int i=0;i<FRAME_COUNT-1;i++){
		sprintf(filename,"sd_hall_sse/hall%06d.pgm",i+1);
 		SavePGM_ui8matrix(sd[i], nrl, nrh, ncl, nch, filename);
	}

	free_ui8matrix(m, nrl, nrh, ncl, nch);
	free_ui8matrix(o, nrl, nrh, ncl, nch);
	free_ui8matrix(v, nrl, nrh, ncl, nch);

	for(long i=0;i<FRAME_COUNT-1;i++)
		free_ui8matrix(sd[i], nrl, nrh, ncl, nch);
}