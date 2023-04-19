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
	int initiale; // variable =1 --> etat initial ;=0 --> n'est pas initial
	int accept; // variable =1 --> etat d'acceptation  ;=0 --> n'est pas d'acceptation
	Transition *Ttrans;	/* pointeur de type transition qui pointe sur un tableau qui va 
	contenir les transitions de l'etat;autrement un tableau dont sa taile=nombre de
	 transitions de l'etat ,et dans chaque cellule on a un variable de type transition*/
};
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
void Ftransition(char* buffer, Etat* pointeurEtat,int nbrNoeud,int *tNbrTrans){ 
	int i=0, j=0, nbr;
	char nbrStr[5];
	nbr=pointeurEtat->numEtat;
	sprintf(nbrStr,"%d", nbr);
    for(i=0;i<255;i++){
	if( buffer[i]==nbrStr[0]){
		if(buffer[i+2]=='-'){/* par ex: nbr -> etat */
	       // printf("%c",buffer[i+5]);
			if(buffer[i+5]=='F'){
				//printf("c\n");
    			pointeurEtat->Ttrans[j].PointeSuiv= NULL;
    			pointeurEtat->accept=1;
    			j++;
    			pointeurEtat->Ttrans=realloc(pointeurEtat->Ttrans,(j+1)*sizeof(Transition));
			}
			else{
			char* pt= &buffer[i+5];
			int value= atoi(pt);
			//	pointeurEtat->Ttrans[j]=malloc(sizeof(transition))
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
	//int *buffer;
	int i=0, j=0;
	Etat** T = malloc(sizeof(Etat*)*nbrNoeud); 
	/* avec la fonction malloc on crée un tableau dynamique qui va contenir des pointeur de type Etat */
   for(i=0;i<nbrNoeud;i++){
   	T[i] = malloc(sizeof(Etat));
	   /*remplir chaque case i du tableau crée au-dessus par une adresse
   	 d'état i*/
   }
    for(i=0;i<nbrNoeud;i++){ /*on fait accés à chaque état i pour la remplir à l'aide de l'adresse stockée dans le tableau (la case i)*/
   		 T[i]->numEtat=i; 
   		   T[i]->initiale=0;
   		     T[i]->accept=0;
   		 T[i]->Ttrans=malloc(sizeof(Transition));/* reservation d'espace pour le tableau de transitions*/
   		  Ftransition(buffer, T[i],nbrNoeud,tNbrTrans);
   		//  printf("tNbrTrans: %d",tNbrTrans[T[i]->numEtat]);
   		nbrTrans=tNbrTrans[i];
   		    for(j=0;j<nbrTrans;j++){
   		    	T[i]->Ttrans[j].PointeSuiv = T[T[i]->Ttrans[j].numSuiv];
   		    	//printf("pour tran %d  =%p",j,T[i]->Ttrans[j].PointeSuiv);
   		    	
		   }
	   }
	   return T;
   }
   
int main(int argc, char*argv[]){
	int i;
	char buffer[265];
	int *tNbrTrans;
	lectureVersBuffer(buffer);
	tNbrTrans=malloc(1*sizeof(int));
/*for(i=0; i<260; i++){
		printf("buffer[%d]=%c\n",i, buffer[i]);
	}*/
	production(buffer,1,tNbrTrans);
		
	return 0;
	
}
