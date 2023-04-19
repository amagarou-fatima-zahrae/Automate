#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
	char *nom;
	char *prenom;
	long *numCompte;
	double solde;
}Compte;
int main(){
	char* chaine;
	chaine=malloc(10*sizeof(char));
	Compte client;
	int*T=malloc(sizeof(int));
	printf("1) T[0]=%d, T[1]=%d\n",T[0], T[1]);
	T[0]=1;
	T[1]=2;
	printf("2) T[0]=%d, T[1]=%d\n",T[0], T[1]);
	printf("Donner le nom du client\n");
	gets(chaine);
	client.nom=malloc(sizeof(char)*(strlen(chaine)+1));
	strcpy(client.nom, chaine);
	printf("client.nom=%s", client.nom);
	//getchar();
}
