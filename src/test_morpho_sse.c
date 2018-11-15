#include <stdio.h>
#include "nrdef.h"
#include "nrutil.h"
#include <string.h>
#include "morpho_sse.h"
#include "test_morpho.h"
#include "test_morpho_sse.h"

/*******************************************************************************************
void test_morpho()
Permet de tester les différentes transformations morphologiques :
ouverture, fermeture, erosion, dilataion. Le modèle de test est la tête du bonhome
présenté dans le sujet du projet.
NOTA : La dilatation et l'erosion sont inversées dans les fichiers de sortie.
Mais en réalité dans notre cas, on considère les pixels à dilater ceux qui sont blancs
(dans le context des algos FrameDiff et SigmaDelta ) alors que dans l'example, la dilation
dilate les pixels noirs 

Par ailleurs une bordure noire se forme sur le images pgm de sortie, cela est normal du fait
que nos matrices de sorties ont été initialisées à 0 ( donc couleur noire ) : l'arrière plan
de la matrice initialisé est noire alors que l'arrière plan de l'image de test est blanc
*******************************************************************************************/
void test_morpho_sse(){
	long nrl = 0;
	long nrh = 0;
	long ncl = 0;
	long nch = 0;
	char *filename ="test1.pgm";
	char *filerosion ="erosion_sse.pgm";
	char *filouverture ="ouverture_sse.pgm";	
	char *filedilatation ="dilatation_sse.pgm";
	char *filefermeture ="fermeture_sse.pgm";
	uint8 **seq0 = LoadPGM_ui8matrix(filename, &nrl, &nrh, &ncl, &nch);
	uint8 **seq = wrapping(seq0,nrl,nrh,ncl,nch);

	uint8 **seqero = erosion_sse(seq,nrl, nrh, ncl, nch);
	uint8 **seqdil = dilatation_sse(seq,nrl, nrh, ncl, nch);
	uint8 **seqouv = ouverture_sse(seq,nrl, nrh, ncl, nch);
	uint8 **seqfer = fermeture_sse(seq,nrl, nrh, ncl, nch);

	/*SavePGM_ui8matrix(seqero, nrl, nrh, ncl, nch, filerosion);
 	SavePGM_ui8matrix(seqdil, nrl, nrh, ncl, nch, filedilatation);
 	SavePGM_ui8matrix(seqouv, nrl, nrh, ncl, nch, filouverture);
 	SavePGM_ui8matrix(seqfer, nrl, nrh, ncl, nch, filefermeture);*/
	
	free_ui8matrix(seq0, nrl, nrh, ncl, nch);	
	free_ui8matrix(seq, nrl-2, nrh+2, ncl-2, nch+2);
	free_ui8matrix(seqero, nrl-EDGE_SSE, nrh+EDGE_SSE, ncl-EDGE_SSE, nch+EDGE_SSE);
	free_ui8matrix(seqdil, nrl-EDGE_SSE, nrh+EDGE_SSE, ncl-EDGE_SSE, nch+EDGE_SSE);
	free_ui8matrix(seqouv, nrl-EDGE_SSE, nrh+EDGE_SSE, ncl-EDGE_SSE, nch+EDGE_SSE);
	free_ui8matrix(seqfer, nrl-EDGE_SSE, nrh+EDGE_SSE, ncl-EDGE_SSE, nch+EDGE_SSE);	
}