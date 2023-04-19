#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"projetFinalFinal.h"

int main(int argc, char*argv[]){
	int i=0, j=0;
	char buffer[300];
	Etat** T;
	int *tNbrTrans;
	Etat* Tnouveau[20];
	int TabCle[20];
	int Tstockage[20];
	int tNbrTrans2[20];
	int tNbrTrans3[20];
	int dimension=0;
	Etat* Tinverse[20];
	int* finale=malloc(sizeof(int));
	int* initial=malloc(sizeof(int));
	int rang=0;
	int nbrNoeud=nbrNoeuds();
	lectureVersBuffer(buffer);
	int somme=0;
	tNbrTrans=malloc(nbrNoeud*sizeof(int));
	T=production(buffer,nbrNoeud,tNbrTrans);
	ecrireDansDot(T,tNbrTrans,nbrNoeud);
	RechercherInitial(T, nbrNoeud, initial, &rang, Tstockage,Tnouveau, TabCle, &somme, &dimension);
	creationNouveau(initial,T, tNbrTrans, &dimension,Tnouveau, &somme, Tstockage, TabCle, &rang,tNbrTrans2);
	int k=0;
	
	ecrireDansDot2(Tnouveau, tNbrTrans2, rang);
	minimisation(Tnouveau, tNbrTrans2, tNbrTrans3, &rang, Tinverse, initial, Tstockage, TabCle, &somme, &dimension);
	ecrireDansDot3(Tnouveau, tNbrTrans2, rang);
	lireDuConsole(Tnouveau, tNbrTrans2,&rang,finale);
	motacceptDuFichier(Tnouveau,tNbrTrans2,&rang,finale);
	for(i=0; i<nbrNoeud;i++){
		free(T[i]->Ttrans);
	}
	free(T);
	free(tNbrTrans);
	free(finale);
	free(initial);
	return 0;
	}
