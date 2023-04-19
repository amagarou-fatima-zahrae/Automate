#include<stdio.h>
#include<stdlib.h>
#include"projetFinalFinal.h"

void inverse(Etat** Tnouveau,int* tNbrTrans2,int* tNbrTrans3, int* rang, Etat** Tinverse){
	int compteur = 0;
	int k =0, i=0, j=0;
    for(i=0 ; i<*rang ; i++){
    		Tinverse[i]= malloc(sizeof(Etat));
    		Tinverse[i]->Ttrans = malloc(sizeof(Transition));
    		Tinverse[i]->numEtat =i  ;  
            tNbrTrans3[i] = 0;
            Tinverse[i]->initiale = 0;
            Tinverse[i]->accept = 0;

	}
		for(i=0;i<*rang;i++){
			
			 if(Tnouveau[i]->accept==1){
		   	tNbrTrans2[i]--;
		   	Tinverse[i]->initiale = 1;
		   }

		for(j=0;j<tNbrTrans2[i];j++){ 
		  
                compteur= Tnouveau[i]->Ttrans[j].numSuiv;
            	k = tNbrTrans3[compteur];
            	  
			      Tinverse[compteur]->Ttrans[k].symbole = Tnouveau[i]->Ttrans[j].symbole;
			      Tinverse[compteur]->Ttrans[k].numSuiv = i;
			      Tinverse[compteur]->Ttrans[k].PointeSuiv=Tnouveau[i];
			      
			       k = tNbrTrans3[compteur] += 1;
			      Tinverse[compteur]->Ttrans = realloc(Tinverse[compteur]->Ttrans,(k+1)*sizeof(Transition)); 

		}
	}
	
           for(i=0;i<*rang;i++){	
                   if(Tnouveau[i]->initiale == 1){
				    Tinverse[i]->accept = 1;
				    Tinverse[i]->Ttrans[tNbrTrans3[i]].PointeSuiv = NULL;
					tNbrTrans3[i] += 1;
			          }
		}	
}
void minimisation(Etat** Tnouveau, int* tNbrTrans2,int* tNbrTrans3, int* rang, Etat** Tinverse, int* initial, int* Tstockage, int* TabCle, int* somme, int* dimension){
	int i=0, nbrNoeud=0;
	for(i=0; i<2; i++){
		inverse(Tnouveau, tNbrTrans2, tNbrTrans3, rang, Tinverse);
		nbrNoeud=*rang;
		*rang=0;
		*somme=0;
		*dimension=0;
		initial=realloc(initial, sizeof(int));
		RechercherInitial(Tinverse, nbrNoeud, initial, rang, Tstockage, Tnouveau, TabCle, somme, dimension);
		creationNouveau(initial, Tinverse, tNbrTrans3,dimension, Tnouveau,somme, Tstockage,TabCle,rang, tNbrTrans2);
	}
}
void ecrireDansDot3(Etat** Tnouveau,int *tNbrTrans2,int nbrNoeud){
	int i,j,nbrTrans;
	FILE *pointfichier;
		pointfichier=fopen("nouveauMinimisation.dot", "w");
		fprintf(pointfichier,"digraph G{\n");
			fprintf(pointfichier,"I [label=\"\", style=invis, height=0]\n");
			fprintf(pointfichier,"F [label=\"\", style=invis, height=0]\n");
		for(i=0; i<nbrNoeud; i++){
			if((Tnouveau[i]->initiale)==1){
				fprintf(pointfichier,"I -> %d\n", i);
		    }
			if((Tnouveau[i]->accept)==1) {
				fprintf(pointfichier,"%d -> F\n", i);
			}
			nbrTrans=tNbrTrans2[i];	
			for(j=0; j<nbrTrans; j++){
		  		if(((Tnouveau[i]->Ttrans[j]).PointeSuiv)!=NULL){
			 		fprintf(pointfichier, "%d -> %d [label=\"%c\"]\n", i, Tnouveau[i]->Ttrans[j].numSuiv, Tnouveau[i]->Ttrans[j].symbole);
				}
			}
			
	}
	fprintf(pointfichier,"}");
}
