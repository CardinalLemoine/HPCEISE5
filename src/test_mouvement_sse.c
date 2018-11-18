#include <stdio.h>
#include "roc.h"
#include "test_mouvement_sse.h"

void fd_routine_sse(){
	//Init vars scalaires
	long nrl = 0;
	long nrh = 0;
	long ncl = 0;
	long nch = 0;

	char filename[256]; //nom du fichier image dans /hall
	uint8 **sequence[FRAME_COUNT]; //L'ensemble des images de la sequence
	uint8 **fdSIMD[FRAME_COUNT-1]; //L'ensemble des images de la sequence apres FD

	//Chargement de tout les frames dans une liste
	printf("Loading PGM sequence...\n");
	for(int i=0;i<FRAME_COUNT;i++){
		sprintf(filename,"hall/hall%06d.pgm",i);
		sequence[i] = LoadPGM_ui8matrix(filename, &nrl, &nrh, &ncl, &nch);	
	}

	//Application de l'algo Frame Difference SIMD
	printf("Applying FD SIMD Algorithm...\n");	
	for(int i=1;i<FRAME_COUNT;i++){
		fdSIMD[i-1] = frame_difference_sse(sequence[i-1],sequence[i], nrl, nrh, ncl, nch);
		/*if(i%10 == 1){
			char filetruth[30];
			sprintf(filetruth, "verite_SIMD/hall%06d.pgm", i-1);
			uint8 **truth_sequence = LoadPGM_ui8matrix(filetruth, &nrl, &nrh, &ncl, &nch);
			uint32 **roc_matrix = roc(truth_sequence, fdSIMD[i-1], nrl, nrh, ncl, nch);
			printf("ROC maxtrix for i=%d\n", i-1);
			display_ui32matrix(roc_matrix, 0, 1, 0, 1, " %5u", "ROC");

			free_ui8matrix(truth_sequence, nrl, nrh, ncl, nch);
			free_ui32matrix(roc_matrix, 0, 1, 0, 1);
		}*/	
	}

	//Sauvegarde output frame difference
	printf("Saving FD SIMD sequence...\n");
	for(int i=0;i<FRAME_COUNT-1;i++){
		sprintf(filename,"fd_hall_sse/hall%06d.pgm",i);
 		SavePGM_ui8matrix(fdSIMD[i], nrl, nrh, ncl, nch, filename);
	}

	//On libere de la bonne memoire precieuse
	printf("Cleaning Matrix...\n");
	for(int i=0;i<FRAME_COUNT-1;i++){
		free_ui8matrix(fdSIMD[i], nrl-EDGE_SSE, nrh+EDGE_SSE, ncl-EDGE_SSE, nch+EDGE_SSE);
		free_ui8matrix(sequence[i], nrl, nrh, ncl, nch);
	}
	free_ui8matrix(sequence[FRAME_COUNT-1], nrl, nrh, ncl, nch);

	printf("Done for FD SIMD routine.\n\n");

}

void sd_routine_sse(){
	long nrl = 0;
	long nrh = 0;
	long ncl = 0;
	long nch = 0;
	uint8 **sequence[FRAME_COUNT];
	uint8 **sdSIMD[FRAME_COUNT-1]; //L'ensemble des images de la sequence apres SD
	char filename[256];

	//Chargement de tout les frames dans une liste
	printf("Loading PGM sequence...\n");
	for(int i=0;i<FRAME_COUNT;i++){
		sprintf(filename,"hall/hall%06d.pgm",i);
		sequence[i] = LoadPGM_ui8matrix(filename, &nrl, &nrh, &ncl, &nch);	
	}
	
	//Application de l'algo Sigma Delta
	printf("Applying SD SIMD Algorithm...\n");
	uint8 **m = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **v = ui8matrix(nrl, nrh, ncl, nch);

	for(int i=nrl; i<=nrh; i++){
		for(int j=ncl; j<=nch; j++){
			m[i][j] = sequence[0][i][j];
			v[i][j] = VMIN;
		}
	}

	for(int i=1; i<FRAME_COUNT; i++){
		sdSIMD[i-1] = sigma_delta_sse(sequence[i], m, v, nrl, nrh, ncl, nch);
		if(i%10 == 1){
			char filetruth[30];
			sprintf(filetruth, "verite_SIMD/hall%06d.pgm", i-1);
			uint8 **truth_sequence = LoadPGM_ui8matrix(filetruth, &nrl, &nrh, &ncl, &nch);
			uint32 **roc_matrix = roc(truth_sequence, sdSIMD[i-1], nrl, nrh, ncl, nch);
			printf("ROC maxtrix for i=%d\n", i-1);
			display_ui32matrix(roc_matrix, 0, 1, 0, 1, " %5u", "ROC");

			free_ui8matrix(truth_sequence, nrl, nrh, ncl, nch);
			free_ui32matrix(roc_matrix, 0, 1, 0, 1);
		}
	}

	//Sauvegarde output frame difference
	printf("Saving SD SIMD sequence...\n");
	for(int i=0;i<FRAME_COUNT-1;i++){
		sprintf(filename,"sd_hall_sse/hall%06d.pgm",i);
 		SavePGM_ui8matrix(sdSIMD[i], nrl, nrh, ncl, nch, filename);
	}
	//On libere de la bonne memoire precieuse
	printf("Cleaning Matrix...\n");
	free_ui8matrix(m, nrl, nrh, ncl, nch);
	free_ui8matrix(v, nrl, nrh, ncl, nch);

	for(int i=0;i<FRAME_COUNT-1;i++){
		free_ui8matrix(sdSIMD[i], nrl-EDGE_SSE, nrh+EDGE_SSE, ncl-EDGE_SSE, nch+EDGE_SSE);
		free_ui8matrix(sequence[i], nrl, nrh, ncl, nch);
	}
	free_ui8matrix(sequence[FRAME_COUNT-1], nrl, nrh, ncl, nch);

	printf("Done for SD SIMD routine.\n\n");
}
