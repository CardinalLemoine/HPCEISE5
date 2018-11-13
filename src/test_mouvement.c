#include <stdio.h>
#include "nrdef.h"
#include "nrutil.h"
#include "test_mouvement.h"
#include "test_morpho.h"
#include <string.h>

/*******************************************************************************************
void fd_sequence()
Applique l'ensemble de la sequence de travail avec leFrame difference.
Cette fonction charge la sequence d'image, applique la FD puis une morpho et enfin sauvegarde
les images en sortie de la FD puis les images sorties de la FD+morpho
*******************************************************************************************/
void fd_routine(){
	long nrl = 0;
	long nrh = 0;
	long ncl = 0;
	long nch = 0;
	char filename[256]; //nom du fichier image dans /hall
	uint8 **sequence[FRAME_COUNT]; //L'ensemble des images de la sequence
	uint8 **fd[FRAME_COUNT-1]; //L'ensemble des images de la sequence apres FD
	uint8 **fd_morpho[FRAME_COUNT-1]; //L'ensemble des images de la sequence FD apres morpho

	//Chargement de tout les frames dans une liste
	printf("Loading PGM sequence...\n");
	for(int i=0;i<FRAME_COUNT;i++){
		sprintf(filename,"hall/hall%06d.pgm",i);
		sequence[i] = LoadPGM_ui8matrix(filename, &nrl, &nrh, &ncl, &nch);	
	}
	
	//Application de l'algo Frame Difference
	printf("Applying FD Algorithm...\n");	
	for(int i=1;i<FRAME_COUNT;i++){
		fd[i-1] = frame_difference(sequence[i-1],sequence[i], nrl, nrh, ncl, nch);	
	}

	//Sauvegarde output frame difference
	printf("Saving FD sequence...\n");
	for(int i=0;i<FRAME_COUNT-1;i++){
		sprintf(filename,"fd_hall/hall%06d.pgm",i);
 		SavePGM_ui8matrix(fd[i], nrl, nrh, ncl, nch, filename);
	}

	//On applique une morpho
	printf("Applying Morpho...\n");
	for(int i=0;i<FRAME_COUNT-1;i++){
 		fd_morpho[i] = erosion(fd[i], nrl, nrh, ncl, nch); 
	}

	//Sauvegarde output frame difference + morpho
	printf("Saving FD+Morpho sequence...\n");
	for(int i=0;i<FRAME_COUNT-1;i++){
		sprintf(filename,"fdmorph_hall/hall%06d.pgm",i);
 		SavePGM_ui8matrix(fd_morpho[i], nrl, nrh, ncl, nch, filename);
	}
	
	//On libere de la bonne memoire precieuse
	printf("Cleaning Matrix...\n");
	for(int i=0;i<FRAME_COUNT-1;i++){
		free_ui8matrix(fd[i], nrl-EDGE, nrh+EDGE, ncl-EDGE, nch+EDGE);
		free_ui8matrix(sequence[i], nrl, nrh, ncl, nch);
	}
	free_ui8matrix(sequence[FRAME_COUNT-1], nrl, nrh, ncl, nch);

	printf("Done for FD sequence.\n\n");	

}

/*******************************************************************************************
void sd_sequence()
Applique l'ensemble de la sequence de travail avec le SigmaDelta.
Cette fonction charge la sequence d'image, applique la SD et sauvegarde
les images en sortie de la SD
*******************************************************************************************/
void sd_routine(){
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
	uint8 **m_1 = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **m = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **o = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **v_1 = ui8matrix(nrl, nrh, ncl, nch);
	uint8 **v = ui8matrix(nrl, nrh, ncl, nch);

	for(int i=nrl; i<nrh; i++)
	{
		for(int j=ncl; j<nch; j++)
		{
			m_1[i][j] = sequence[0][i][j];
			v_1[i][j] = VMIN;
		}
	}

	for(long i=1; i<FRAME_COUNT; i++)
	{
		sd[i-1]=sigma_delta(sequence[i], m, m_1, o, v, v_1 , nrl, nrh, ncl, nch);
		for(long j=nrl; j<nrh; j++)
		{
			for(long k=ncl; k<nch; k++)
			{
				m_1[j][k] = m[j][k];
				v_1[j][k] = v[j][k];
			}
		}
	}

	//Sauvegarde output frame difference
	printf("Saving SD sequence...\n");
	for(int i=0;i<FRAME_COUNT-1;i++){
		sprintf(filename,"sd_hall/hall%06d.pgm",i);
 		SavePGM_ui8matrix(sd[i], nrl, nrh, ncl, nch, filename);
	}

	//On applique une morpho
	printf("Applying Morpho...\n");
	for(int i=0;i<FRAME_COUNT-1;i++){
 		sd_morpho[i] = erosion(sd[i], nrl, nrh, ncl, nch); 
	}

	//Sauvegarde output frame difference + morpho
	printf("Saving FD+Morpho sequence...\n");
	for(int i=0;i<FRAME_COUNT-1;i++){
		sprintf(filename,"sdmorph_hall/hall%06d.pgm",i);
 		SavePGM_ui8matrix(sd_morpho[i], nrl, nrh, ncl, nch, filename);
	}

	//On libere de la bonne memoire precieuse
	printf("Cleaning Matrix...\n");
	free_ui8matrix(m_1, nrl, nrh, ncl, nch);
	free_ui8matrix(m, nrl, nrh, ncl, nch);
	free_ui8matrix(o, nrl, nrh, ncl, nch);
	free_ui8matrix(v_1, nrl, nrh, ncl, nch);
	free_ui8matrix(v, nrl, nrh, ncl, nch);
	for(int i=0;i<FRAME_COUNT-1;i++){
		free_ui8matrix(sd[i], nrl-EDGE, nrh+EDGE, ncl-EDGE, nch+EDGE);
		free_ui8matrix(sequence[i], nrl, nrh, ncl, nch);
	}
	free_ui8matrix(sequence[FRAME_COUNT-1], nrl, nrh, ncl, nch);
	printf("Done for SD sequence.\n\n");

}
