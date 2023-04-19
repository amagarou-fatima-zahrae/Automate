#include<stdio.h>
#include<stdlib.h>
int main(){
	char chaine[10];
	int nbr;
	nbr=20;
	char carac[]="20";
	sprintf(chaine, "%d", nbr);
	printf("%s", chaine);
	if(chaine[0]==carac[0]){
		printf("vrai");
	}
	else{
		printf("f");
	}
	return 0;
}
