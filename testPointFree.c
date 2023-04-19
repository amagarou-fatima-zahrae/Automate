#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
	int* pointeurTest=malloc(sizeof(int)*5);
	int i;
	pointeurTest[0]=6;
	pointeurTest[1]=7;
	pointeurTest[2]=8;
	pointeurTest[3]=9;
	pointeurTest[4]=10;
	printf("pt avant=%x\n", pointeurTest);
	for(i=0; i<5; i++){
	printf("T[%d]=%d\n", i,pointeurTest[i]);	
	}
	//free(pointeurTest);
	pointeurTest=realloc(pointeurTest, sizeof(int));
	printf("pt apres=%x\n", pointeurTest);
	for(i=0; i<5; i++){
	printf("T[%d]=%d\n", i,pointeurTest[i]);	
	}
	
	return 0;
}
