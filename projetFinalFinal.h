#ifndef projetFinalFinal
#define projetFinalFinal
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

int nbrNoeuds(); /*fonction qui va retourner le nombre des etats de l'automate */
Etat** production(char *buffer,int nbrNoeud,int *tNbrTrans); /* fonction de stockage */
void Ftransition(char* buffer, Etat* pointeurEtat,int nbrNoeud,int *tNbrTrans);/*fonction chargé de 
scanner les données du fichier.dot:Elle a comme arguments:
 * buffer:pointeur pointe sur le tableau buffer où on a stocké les données du fichier
 Etat* pointeurEtat:pointeur sur l'etat
 *tNbrTrans:pointeur pointe sur le tableau ou on a stocker le nombre de transitions de chaque etat*/
void lectureVersBuffer(char buffer[]); /* buffer est un pointeur pointe sur un tableau où on va stocker
une copie de fichier.dot afin de faire un accés direct au tableau au lieu du disque sur
ce qui minimise le temps d'accés et éviter de charger chaque fois le fichier du disque dur 
dans la mémoire RAM.*/ 
void ecrireDansDot(Etat** T,int *tNbrTrans,int nbrNoeud);
void ecrireDansDot2(Etat** T,int *tNbrTrans,int nbrNoeud); /*fonction pour écrire l'automate résultant dans le langage dot*/
int verification(int** ptTabSymb, int *rang,int *Tabtaille, int numSymbole,int *tabCle,int *Tstockage,char *symboles, Etat** Tnouveau);
void RechercherInitial(Etat** T,int nbrNoeud,int* Initial, int* rang,int* Tstockage,Etat** Tnouveau,int *TabCle,int *somme,int *dimension);
void creationNouveau(int* tabEnsemble,Etat** T,int* tNbrTrans,int *dimension,Etat** Tnouveau,int *somme,int *Tstockage,int *TabCle, int *rang, int* tNbrTrans2);
void inverse(Etat** Tnouveau,int* tNbrTrans2,int* tNbrTrans3, int* rang, Etat** Tinverse);
void minimisation(Etat** Tnouveau, int* tNbrTrans2,int* tNbrTrans3, int* rang, Etat** Tinverse, int* initial, int* Tstockage, int* TabCle, int* somme, int* dimension);
void ecrireDansDot3(Etat** Tnouveau,int *tNbrTrans2,int nbrNoeud);
int lireDuConsole(Etat**  Tnouveau,int *tNbrTrans2,int *rang,int *finale);
int Etatinitial (Etat **Tnouveau ,int *rang);
int Etatfinale(Etat** Tnouveau ,int* finale,int *rang);
int verifMotAccept(char* ch,int numEtat ,Etat**  Tnouveau,int* tNbrTrans2,int *rang,int *finale,int dimFin);
void motacceptDuFichier(Etat** Tnouveau, int* tNbrTrans2, int *rang,int* finale);

#endif


