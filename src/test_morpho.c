#include <stdio.h>
#include "nrdef.h"
#include "nrutil.h"
#include <string.h>
#include "test_morpho.h"

/*******************************************************************************************
uint8** wrapping()
Dans notre projet, toute image analysée par un algo de mouvevement renvoit une matrice de
dimension de l'image plus un EDGE ( ou bord ) qu'on a rajouté pour eviter un out of range lors de
l'application des opérations morpho logiques. Or nos images de test sont déjà binaire et n'ont
pas subit l'ajout de EDGE. On fait donc un wrapping pour rendre l'image de test cohérent
lors des opérations morphologiques
*******************************************************************************************/
uint8** wrapping(uint8 **m,long nrl,long nrh,long ncl, long nch){
	//Creation matrice 5x6	
	uint8 **m2 = ui8matrix(nrl-2, nrh+2, ncl-2, nch+2);
	//On affacte les vaeurs
	for(int i=0;i<=nrh;i++){
		for(int j=0;j<=nch;j++){
			m2[i][j] = m[i][j];
		}
	}
	return m2;
	
}

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
void test_morpho(){
	long nrl = 0;
	long nrh = 0;
	long ncl = 0;
	long nch = 0;
	char *filename ="test1.pgm";
	char *filerosion ="erosion.pgm";
	char *filouverture ="ouverture.pgm";	
	char *filedilatation ="dialatation.pgm";
	char *filefermeture ="fermeture.pgm";
	printf("Performing unitary tests for morpho transformation...");
	uint8 **seq0 = LoadPGM_ui8matrix(filename, &nrl, &nrh, &ncl, &nch);
	uint8 **seq = wrapping(seq0,nrl,nrh,ncl,nch);

	uint8 **seqero = erosion(seq,nrl, nrh, ncl, nch);
	uint8 **seqdil = dilatation(seq,nrl, nrh, ncl, nch);
	uint8 **seqouv = ouverture(seq,nrl, nrh, ncl, nch);
	uint8 **seqfer = fermeture(seq,nrl, nrh, ncl, nch);

 	SavePGM_ui8matrix(seqero, nrl, nrh, ncl, nch, filerosion);
 	SavePGM_ui8matrix(seqdil, nrl, nrh, ncl, nch, filedilatation);
 	SavePGM_ui8matrix(seqouv, nrl, nrh, ncl, nch, filouverture);
 	SavePGM_ui8matrix(seqfer, nrl, nrh, ncl, nch, filefermeture);

	printf("Done.\n\n");

}

