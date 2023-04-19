#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"projetFinalFinal.h"

int nbrNoeuds(){
	int nbr=0;
	FILE* pointerFileRecup=NULL;
 	pointerFileRecup=_popen("gc.exe -n C:\\Users\\DELL\\Desktop\\projetFinalFinal\\work1.dot","r"); /* gc:c'est 
	un outil de Graphviz qui permet de faire des statistiques sur le fichier .dot Dans ce cas, la commande -n calcule le nombre des états
	dans un ficher.dot à l'aide de la console cmd */
	if(pointerFileRecup==NULL){
		exit(EXIT_FAILURE);
	//	system("gc.exe -n C:\\Users\\DELL\\Desktop\\projetFinalFinal\\work1.dot");
	}
	fscanf(pointerFileRecup, "%d", &nbr);
	pclose(pointerFileRecup);
	return nbr-2; /* le langage dot ne distingue pas les états initiaux et finaux des autres
	états --> pour cela, dans notre fichier.dot, on a ajouté deux états: I et F,I:qui a comme succeseurs les états initiaux du graphe
	 avec le I[label="" style=invis, height=0] (pour que I soit invisible et il s'affiche juste
	 juste l'arc sortant de lui.)
	 On applimeme logique pour F qui a comme antécédents les états finaux */
}

Etat** production(char *buffer,int nbrNoeud,int *tNbrTrans){
	int nbrTrans=0;
	int i=0, j=0;
	Etat** T = malloc(sizeof(Etat*)*nbrNoeud);
	/* avec la fonction malloc on crée un tableau dynamique qui va contenir des pointeur de type Etat */
   for(i=0;i<nbrNoeud;i++){
   	T[i] = malloc(sizeof(Etat));
   	
	   /*remplir chaque case i du tableau crée au-dessus par une adresse
   	 d'état i*/
   }
    for(i=0;i<nbrNoeud;i++){
	 /*on fait accés à chaque état i pour la remplir à l'aide de l'adresse stockée dans le tableau (la case i)*/
   		 T[i]->numEtat=i; 
   		   T[i]->initiale=0;
   		     T[i]->accept=0;
   		 T[i]->Ttrans=malloc(sizeof(Transition));
	/* reservation d'espace pour le tableau de transitions*/
   		  Ftransition(buffer, T[i],nbrNoeud,tNbrTrans);
   		nbrTrans=tNbrTrans[i];
   		    for(j=0;j<nbrTrans;j++){
   		    	if(T[i]->accept!=1){
   		    		T[i]->Ttrans[j].PointeSuiv = T[T[i]->Ttrans[j].numSuiv];
		   }
	   }
	}
	   
	   return T;
   }
	
void lectureVersBuffer(char *buffer){
	int i=0;
	
	FILE *fp; /* fp: pointeur sur le fichier */
	fp=fopen("work1.dot","r+");/*ouvrir le fichier.dot*/
	
	if (fp != NULL)
    {
     do{
        buffer[i] = fgetc(fp); /* stocker chaque donnée du fichier dans le tableau */
        i++;
        } while (buffer[i] != EOF); 
    }
    else
    {
        printf("Impossible d'ouvrir le fichier.dot");
    }
    
}

void Ftransition(char* buffer, Etat* pointeurEtat,int nbrNoeud,int *tNbrTrans){ 
	int i=0, j=0, nbr;
	char nbrStr[5];
	nbr=pointeurEtat->numEtat;
	sprintf(nbrStr,"%d", nbr);
    for(i=0;i<246;i++){
	if( buffer[i]==nbrStr[0]){
		if(buffer[i+2]=='-'){/* par ex: nbr -> etat */
			if(buffer[i+5]=='F'){
    			pointeurEtat->Ttrans[j].PointeSuiv= NULL;
    			pointeurEtat->accept=1;
    			j++;
    			pointeurEtat->Ttrans=realloc(pointeurEtat->Ttrans,(j+1)*sizeof(Transition));
    			
			}
			else{
			char* pt= &buffer[i+5];
			int value= atoi(pt);
			  pointeurEtat->Ttrans[j].numSuiv=value;
			  pointeurEtat->Ttrans[j].symbole=buffer[i+15];
			  // par ex: 2 -> 5 [label="a"]	
				j++;
				pointeurEtat->Ttrans=realloc(pointeurEtat->Ttrans,(j+1)*sizeof(Transition));
               
			}
		}
		else if(buffer[i-2]=='>'){ /* par ex: etat -> nbr */
			if(buffer[i-5]=='I'){
				pointeurEtat->initiale=1;
			}		
		}
		
      }
    }
    tNbrTrans[pointeurEtat->numEtat]=j;
}

void ecrireDansDot(Etat** T,int *tNbrTrans,int nbrNoeud){
	int i,j,nbrTrans;
	FILE *pointfichier;
		pointfichier=fopen("nouveau.dot", "w");
		fprintf(pointfichier,"digraph G{\n");
		printf("nbrNeuds: %d\n",nbrNoeud);
			fprintf(pointfichier,"I [label=\"\", style=invis, height=0]\n");
			fprintf(pointfichier,"F [label=\"\", style=invis, height=0]\n");
		for(i=0; i<nbrNoeud; i++){
			if((T[i]->initiale)==1){
				fprintf(pointfichier,"I -> %d\n", i);
		    }
			if((T[i]->accept)==1) {
				fprintf(pointfichier,"%d -> F\n", i);
			}
			nbrTrans=tNbrTrans[i];	
			for(j=0; j<nbrTrans; j++){
		  		if(((T[i]->Ttrans[j]).PointeSuiv)!=NULL){
			 		fprintf(pointfichier, "%d -> %d [label=\"%c\"]\n", i, T[i]->Ttrans[j].numSuiv, T[i]->Ttrans[j].symbole);
				}
			}
			
	}
	fprintf(pointfichier,"}");
	
}



