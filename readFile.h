#ifndef __READ__
#define __READ__

#define TAILLE_MAX 1000 //Nb de lignes du fichier donné en param

//Fonction permettant de stocker ligne par ligne le fichier 
//dont le chemin est donné en param dans le tableau donné aussi en param
int fichierTotab(char *cheminFichier, char contenuFichier[TAILLE_MAX]);
int getNbEtats(char contenuFichier[TAILLE_MAX]);
int getEtatInitial(char contenuFichier[TAILLE_MAX]);
int getEtatFinal(char contenuFichier[TAILLE_MAX]);
char* getAlphabet(char contenuFichier[]);
int getNbTrans(int etat, char contenuFichier[TAILLE_MAX]);
int tailleAlphabet(char contenuFichier[TAILLE_MAX]);

#endif



