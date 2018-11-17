#include "roc.h"

/*************************************************************************************
uint8** roc()
Renvoie une matrice roc de dimension 2x2 permettant de comparer les images de 
sortie des algo de mouvement avec ceux des images de vérité terrain
*************************************************************************************/
uint32** roc(uint8 **truth_frame, uint8 **test_frame,long nrl,long nrh,long ncl, long nch){
	uint32 **roc_matrix = ui32matrix(0, 1, 0, 1);
	roc_matrix[0][0] = 0;
	roc_matrix[0][1] = 0;
	roc_matrix[1][0] = 0;
	roc_matrix[1][1] = 0;

	for(int i=nrl;i<=nrh;i++){
		for(int j=ncl;j<=nch;j++){
			/*vrai positif*/
			if((truth_frame[i][j] == 255) && (test_frame[i][j] == 255)){
				roc_matrix[0][0]++;			
			}
			/*Vrai negatif*/
			else if((truth_frame[i][j] == 0) && (test_frame[i][j] == 0)){
				roc_matrix[1][1]++;			
			}
			/*Faux Negatif : On a considéré que c'etait immobile alors que c'etait en mouvement*/
			else if((truth_frame[i][j] == 255) && (test_frame[i][j] == 0)){
				roc_matrix[0][1]++;	
			}
			/*Faux Positif : On a considéré que c'etait en mouvement alors que c'etait immobile*/
			else{
				roc_matrix[1][0]++;			
			}
		}
	}
	return roc_matrix;
}