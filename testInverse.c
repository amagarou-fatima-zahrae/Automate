#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Transition Transition;
typedef struct Etat Etat;
struct Transition{
	int numSuiv;
	Etat *PointeSuiv;
	char symbole;
};
struct Etat{ 
	int numEtat; 
	int initiale; 
	int accept; 
	Transition *Ttrans;	
};

int nbrNoeuds(){
	int nbr=0;
	FILE* pointerFileRecup=NULL;
 	pointerFileRecup=_popen("gc.exe -n C:\\Graphviz\\automate\\work1.dot","r"); /* gc:c'est 
	un outil de Graphviz qui permet de faire des statistiques sur le fichier .dot Dans ce cas, la commande -n calcule le nombre des états
	dans un ficher.dot à l'aide de la console cmd */
	if(pointerFileRecup==NULL){
		exit(EXIT_FAILURE);
		system("gc.exe -n C:\\Graphviz\\automate\\work1.dot");
	}
	fscanf(pointerFileRecup, "%d", &nbr);
	pclose(pointerFileRecup);
	return nbr-2; /* le langage dot ne distingue pas les états initiaux et finaux des autres
	états --> pour cela, dans notre fichier.dot, on a ajouté deux états: I et F,I:qui a comme succeseurs les états initiaux du graphe
	 avec le I[label="" style=invis, height=0] (pour que I soit invisible et il s'affiche juste
	 juste l'arc sortant de lui.)
	 On applimeme logique pour F qui a comme antécédents les états finaux */
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
//Convertir le fichier.dot en graphe sous forme Image
void affichagePremier(){
	int indice;
	system("cd C:\\Graphviz\\bin");
  	indice=system("dot.exe -Tpng C:\\Graphviz\\automate\\nouveau.dot -o C:\\Graphviz\\automate\\affichageAutomate2.png");
  	if(indice==0){
  		printf("Veuillez trouver l'image sous forme png en suivant le lien:C:\\Graphviz\\automate\\affichageAutomate.png");
	  }
	}
	
void lectureVersBuffer(char *buffer){
	int i=0;
	
	FILE *fp; /* fp: pointeur sur le fichier */
	fp=fopen("C:\\Graphviz\\automate\\work1.dot","r+");/*ouvrir le fichier.dot*/
	
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

void ecrireDansDot(Etat** T,int *tNbrTrans,int nbrNoeud){
	int i,j,nbrTrans;
	FILE *pointfichier;
		pointfichier=fopen("C:\\Graphviz\\automate\\nouveau.dot", "w");
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

		for(j=0;j<tNbrTrans2[i];j++){ //tableau de nbr de transition
		  
                
            	compteur = Tnouveau[i]->Ttrans[j].numSuiv;
            	k = tNbrTrans3[compteur];
            	  
            	 // Tinverse[compteur]->numEtat = Tnouveau[i]->trans[j].numSuiv;
			      Tinverse[compteur]->Ttrans[k].symbole = Tnouveau[i]->Ttrans[j].symbole; //table Ttrans a resoudre
			      Tinverse[compteur]->Ttrans[k].numSuiv = i;
			      
			       k = tNbrTrans3[compteur] += 1;
			      Tinverse[compteur]->Ttrans = realloc(Tinverse[compteur]->Ttrans,(k+1)*sizeof(Transition)); //pour avoir meme taille de rang
            	  // est ce que je peux le creer avant de remlir le rang car j'ai un malloc de rang

		}
	}
	
    for(i=0;i<*rang;i++){	
                   if(Tnouveau[i]->initiale == 1){
			
				    Tinverse[i]->accept = 1;
				    Tinverse[i]->Ttrans[tNbrTrans3[i]].PointeSuiv = NULL;

			          }
		}	
}
void minimisation(Etat** Tnouveau, int* tNbrTrans2,int* tNbrTrans3, int* rang, Etat** Tinverse, int* initial, int* Tstockage, int* TabCle, int* somme, int* dimension){
	int nbrNoeud=0;
	inverse(Tnouveau, tNbrTrans2, tNbrTrans3, rang, Tinverse);
	nbrNoeud=*rang;
	*rang=0;
	*somme=0;
	*dimension=0;
	initial=realloc(initial, sizeof(int));
	RechercherInitial(Tinverse, nbrNoeud, initial, rang, Tstockage, Tnouveau, TabCle, somme, dimension);
	creationNouveau(initial, Tinverse, tNbrTrans3,dimension, Tnouveau,somme, Tstockage,TabCle,rang, tNbrTrans2);
	Tinverse=realloc(Tinverse, (*rang )* sizeof(Etat*));
	inverse(Tnouveau, tNbrTrans2, tNbrTrans3, rang, Tinverse);
	nbrNoeud=*rang;
	*rang=0;
	*somme=0;
	*dimension=0;
	initial=realloc(initial, sizeof(int));
	creationNouveau(initial, Tinverse, tNbrTrans3,dimension, Tnouveau,somme, Tstockage,TabCle,rang, tNbrTrans2);
	Tinverse=realloc(Tinverse, (*rang )* sizeof(Etat*));	
}
int main(int argc, char*argv[]){
	int i=0;
	char buffer[300];
	Etat** T;
	int *tNbrTrans;
	int*Tstockage=malloc(sizeof(int));
	
	int dimension=0;
	int rang=0;
	//int* initial=malloc(sizeof(int));
	//Etat** Tnouveau=malloc(sizeof(Etat*));
	//int* tNbrTrans2=malloc((rang+1)*sizeof(int));
	//int *TabCle=malloc(sizeof(int));
	Etat** Tinverse = malloc((rang)*sizeof(Etat)); // remplir Tinverse
	int *tNbrTrans3 = malloc((rang)*sizeof(int));
	int nbrNoeud=nbrNoeuds();
	lectureVersBuffer(buffer);
	int somme=0;
	tNbrTrans=malloc(nbrNoeud*sizeof(int));
	T=production(buffer,nbrNoeud,tNbrTrans);
	inverse(T,tNbrTrans, tNbrTrans3, &nbrNoeud,Tinverse);
	ecrireDansDot(Tinverse,tNbrTrans3,nbrNoeud);
	affichagePremier();
	
	
	//RechercherInitial(T, nbrNoeud, initial, &rang, Tstockage,Tnouveau, TabCle, &somme, &dimension);
	//creationNouveau(initial,T, tNbrTrans, &dimension,Tnouveau, &somme, Tstockage, TabCle, &rang,tNbrTrans2);
/*	for(i=0; i<somme; i++)
{
	printf("somme=%d, rang=%d, Tstock[%d]=%d", somme, rang,i, Tstockage[i]);
	}	*/
	//printf("cc");
//	ecrireDansDot2(Tnouveau,tNbrTrans2,rang);
//	affichageDeuxieme();
	
	for(i=0; i<nbrNoeud;i++){
		free(T[i]->Ttrans);
	}
	free(T);
	free(tNbrTrans);
	return 0;
	}
