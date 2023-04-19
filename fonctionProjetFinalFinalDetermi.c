#include<stdio.h>
#include<stdlib.h>
#include"projetFinalFinal.h"

void RechercherInitial(Etat** T,int nbrNoeud,int* Initial, int* rang,int* Tstockage,Etat** Tnouveau,int *TabCle,int *somme,int *dimension){
  	int i=0;
  	for(i=0;i<nbrNoeud;i++){
  		if(T[i]->initiale==1){
            
  		    Initial[*dimension]=i;
		  (*dimension)++;	  	
		  Initial=realloc(Initial, ((*dimension)+1)*sizeof(int));
		  }
	  }
	Tnouveau[*rang]= malloc(sizeof(Etat));
	TabCle[*rang]=*dimension;
	Tnouveau[*rang]->numEtat=*rang;
	Tnouveau[*rang]->initiale=1;
	Tnouveau[*rang]->accept=0;

	for(i=0;i<*dimension;i++){
	 Tstockage[i]=Initial[i];
     }
     (*somme)+=(*dimension);
 }
  void creationNouveau(int* tabEnsemble,Etat** T,int* tNbrTrans,int *dimension,Etat** Tnouveau,int *somme,int *Tstockage,int *TabCle, int *rang, int* tNbrTrans2){
	 int i=0,j=0,k=0,compteur=0,existant=0,pos=0;

	int Tabtaille[5];
	char symboles[5];
	int* ptTabSymb[5];

   	int compteur2=0;
  
   		(*rang)++;
  	

	
 	for(i=0;i<*dimension;i++){
 		for(j=0;j<tNbrTrans[tabEnsemble[i]];j++){
 			pos=0;
 		if(T[tabEnsemble[i]]->Ttrans[j].PointeSuiv==NULL){
 			compteur2=1;
 		}
		if(T[tabEnsemble[i]]->Ttrans[j].PointeSuiv!=NULL){
 		  existant=0;
 		  
		  for(compteur=0;compteur<k;compteur++){
		   	if(T[tabEnsemble[i]]->Ttrans[j].symbole==symboles[compteur]){
		   			existant=1;
		   			pos=compteur;
		   			break;
        	}
		   }
		   if(!existant){
		   	symboles[k]=T[tabEnsemble[i]]->Ttrans[j].symbole;
		   	 ptTabSymb[k]=malloc(5*sizeof(int));
		   	 ptTabSymb[k][0]=T[tabEnsemble[i]]->Ttrans[j].numSuiv;
		   	 Tabtaille[k]=1;
 	         k++;
		  }	
		  else{
		  	existant=0;
		  	
		  	for(compteur=0;compteur<Tabtaille[pos];compteur++){
		  		if(ptTabSymb[pos][compteur]==T[tabEnsemble[i]]->Ttrans[j].numSuiv){
		  			existant=1;
		  			break;
				  }
			  }
			  if(!existant){
			(ptTabSymb[pos])[Tabtaille[pos]]=T[tabEnsemble[i]]->Ttrans[j].numSuiv;
		    (Tabtaille[pos])++;
			  }	
		  }
		}
		}
	}
	k=k+compteur2;
	tNbrTrans2[*rang-1]=k;
	Tnouveau[*rang-1]->Ttrans=malloc((5)*sizeof(Transition));
	if(compteur2){
	 Tnouveau[*rang-1]->accept=1;
	 Tnouveau[*rang-1]->Ttrans[k-1].PointeSuiv=NULL;
	 k--;
	}  
	for(i=0; i<k; i++){ 
	  ptTabSymb[i][Tabtaille[i]]=(*rang)-1;
	} 

	for(i=0; i<k; i++){
	if(verification(ptTabSymb,rang, Tabtaille, i,TabCle, Tstockage, symboles, Tnouveau)){
	   Tnouveau[*rang]= malloc(sizeof(Etat));	
	   Tnouveau[*rang]->accept=0;
	   Tnouveau[*rang]->initiale=0;
	   TabCle[*rang]=Tabtaille[i];
	   Tnouveau[*rang]->numEtat=*rang;
	   Tnouveau[ptTabSymb[i][Tabtaille[i]]]->Ttrans[i].numSuiv=Tnouveau[*rang]->numEtat;
	   Tnouveau[ptTabSymb[i][Tabtaille[i]]]->Ttrans[i].PointeSuiv=Tnouveau[*rang];
	   Tnouveau[ptTabSymb[i][Tabtaille[i]]]->Ttrans[i].symbole=symboles[i];
     	for(compteur=*somme,j=0; compteur<*somme+Tabtaille[i]; compteur++,j++){
    	   Tstockage[compteur]=ptTabSymb[i][j];
    	 }
    	
    	 (*somme)+=Tabtaille[i];
    
       *dimension=Tabtaille[i];
     creationNouveau(ptTabSymb[i],T,tNbrTrans,dimension,Tnouveau,somme,Tstockage,TabCle,rang, tNbrTrans2);
    
   }
 
   }
 

}

	int verification(int** ptTabSymb, int *rang,int *Tabtaille, int numSymbole,int *tabCle,int *Tstockage,char *symboles, Etat** Tnouveau){
		
		int j=0,i=0,l=0,s=0,present=0,copieSum=0;
		for(i=0; i<*rang; i++){
		if(tabCle[i]==Tabtaille[numSymbole]){
			copieSum=0;
		  for(j=0;j<i;j++){
				copieSum+=tabCle[j];
			}
		  for(l=copieSum; l<copieSum+Tabtaille[numSymbole]; l++){ 
		  	present=0;
		  	  for(s=0;s<Tabtaille[numSymbole];s++){
		  	  	if(Tstockage[l] == ptTabSymb[numSymbole][s]){
		  	  		present=1;
				}
	           }
	   	if(present==0){
		    break;
	 }
	 if(present==1){
	 	 continue;
	 }
 	
		
	}
	if(present){
	Tnouveau[ptTabSymb[numSymbole][Tabtaille[numSymbole]]]->Ttrans[numSymbole].numSuiv=Tnouveau[i]->numEtat;
	Tnouveau[ptTabSymb[numSymbole][Tabtaille[numSymbole]]]->Ttrans[numSymbole].PointeSuiv=Tnouveau[i];
	Tnouveau[ptTabSymb[numSymbole][Tabtaille[numSymbole]]]->Ttrans[numSymbole].symbole=symboles[numSymbole];
	return 0;      
	}
	
 }
}

   return 1;
   
   
}
 void ecrireDansDot2(Etat** Tnouveau,int *tNbrTrans2,int nbrNoeud){
	int i,j,nbrTrans;
	FILE *pointfichier;
		pointfichier=fopen("nouveauDeterministe.dot", "w");
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
