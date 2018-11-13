#include <stdio.h>
#include "nrdef.h"
#include "nrutil.h"
#include <string.h>
#include <stdlib.h>

/*************************************************************************************
uint8** roc()
Renvoie une matrice roc de dimension 2x2 permettant de comparer les images de 
sortie des algo de mouvement avec ceux des images de vérité terrain
*************************************************************************************/
uint8** roc(uint8 **truth_frame, uint8 **test_frame,long nrl,long nrh,long ncl, long nch){
	uint8 **roc_matrix = ui8matrix(0, 1, 0, 1);
	for(int i=0;i<=nrh;i++){
		for(int j=0;j<=nch;j++){
			/*vrai positif*/
			if((truth_frame[i][j] == 255) && (test_frame[i][j] == 255)){
				roc_matrix[0][0] += 1;			
			}
			/*Vrai negatif*/
			else if((truth_frame[i][j] == 0) && (test_frame[i][j] == 0)){
				roc_matrix[1][1] += 1;			
			}
			/*Faux Negatif : On a considéré que c'etait immobile alors que c'etait en mouvement*/
			else if((truth_frame[i][j] == 255) && (test_frame[i][j] == 0)){
				roc_matrix[0][1] += 1;	
			}
			/*Faux Positif : On a considéré que c'etait en mouvement alors que c'etait immobile*/
			else{
				roc_matrix[1][0] += 1;			
			}
		}
	}
	return roc_matrix;
}
