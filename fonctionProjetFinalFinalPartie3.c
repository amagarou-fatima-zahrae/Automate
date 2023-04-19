#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"projetFinalFinal.h"
int Etatinitial (Etat **Tnouveau ,int *rang){
	int i;
	int numEtat;
	for(i=0;i<*rang;i++){
		if(Tnouveau[i]->initiale){
			numEtat=i;
			break;
		}
	}
	
	return numEtat;
}
int Etatfinale(Etat** Tnouveau ,int* finale,int *rang){
	int i=0,k=0,dimFin=0;
	for(i=0;i<*rang;i++){
		if(Tnouveau[i]->accept){
			finale[k]=i;
			k++;
			dimFin++;
			finale=realloc(finale,(k+1)*sizeof(int));
		}
	}
	return dimFin;
}
int lireDuConsole(Etat**  Tnouveau,int* tNbrTrans2,int *rang,int *finale){ //fonction min
 char ch[20];
 int k=0,i=0,j=0,trouver=0,accepter=0;
 int numEtat,dimFin;
 printf(" \nveuillez enter un mot a verifier:\n");
 scanf("%s",ch);
 numEtat=Etatinitial(Tnouveau ,rang);
 dimFin=Etatfinale(Tnouveau ,finale,rang);

	for(k=0;k<strlen(ch);k++){
		for(i=0;i<*rang;i++){
			trouver=0;
			if(numEtat==i){
				for(j=0;j<tNbrTrans2[i];j++){
				  if(Tnouveau[i]->Ttrans[j].PointeSuiv!=NULL){
					 if(ch[k]==Tnouveau[i]->Ttrans[j].symbole){
						numEtat=Tnouveau[i]->Ttrans[j].numSuiv;
						trouver=1;
						break;
					 }
			    	}
				}
				if(!trouver){
				printf("\nLe mot <%s> est non accepte \ncar l\'automate est coince et il n\'y a pas de transition sur %c depuis l\'etat %d\n\n",ch,ch[k],numEtat);
					return 0;
				}
			}
			if(trouver){
				break;
			}
		}
	}
	if(k==strlen(ch) && trouver==1){
		accepter=0;
		for(i=0;i<dimFin;i++){
			if(numEtat==finale[i]){
				printf("Le mot <%s> est accepte\n\n\n ",ch);
				accepter=1;
				break;
			}
		}
		if(!accepter){
			printf("\nLe mot <%s> est non accepte\nLe mot est lu mais l\'automate n\'est pas dans un etat d\'accepation <%d>\n\n",ch,numEtat);
		}
	}
	return 0;
}
int verifMotAccept(char* ch,int numEtat ,Etat**  Tnouveau,int* tNbrTrans2,int *rang,int *finale,int dimFin){
	int i=0,j=0,k=0,trouver=0,accepter=0;
	for(k=0;k<strlen(ch);k++){
		for(i=0;i<*rang;i++){
			trouver=0;
			if(numEtat==i){
				for(j=0;j<tNbrTrans2[i];j++){
				  if(Tnouveau[i]->Ttrans[j].PointeSuiv!=NULL){
					 if(ch[k]==Tnouveau[i]->Ttrans[j].symbole){
						numEtat=Tnouveau[i]->Ttrans[j].numSuiv;
						trouver=1;
						break;
					 }
			    	}
				}
				if(!trouver){
					return 0;
				}
			}
			if(trouver){
				break;
			}
		}
	}
	if(k==strlen(ch) && trouver==1){
		for(i=0;i<dimFin;i++){
			if(numEtat==finale[i]){
			printf("\n Le mot: <%s> \n ",ch);
			return 1;
			}
		}
	}
	return 0;
}

void motacceptDuFichier(Etat** Tnouveau, int* tNbrTrans2, int *rang,int* finale){
	FILE* f1=NULL;
	FILE* f2=NULL;
	char tab[20];
	int etat=0,dimfinale=0;
	etat=Etatinitial(Tnouveau ,rang);
	f1=fopen("file0.txt","r");
	f2=fopen("file1.txt","w"); 
	
	dimfinale = Etatfinale(Tnouveau,finale,rang);
	
	if(f1 != NULL && f2 != NULL){
		printf("La liste des mots contenus dans le fichier.txt et engendres par l\'automate sont:\n ");
		while(!feof(f1)){
	    	fscanf(f1,"%s",tab);
			if(verifMotAccept(tab, etat,Tnouveau, tNbrTrans2,rang,finale,dimfinale )) 
		    fprintf(f2,"%s \n ",tab);
		}
	}

	else{
		printf("Fichier introuvable");
	}
	fclose(f1);	
	fclose(f2);
}


