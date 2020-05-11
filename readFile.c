#include <stdio.h>
#include <string.h>
#include "readFile.h"
#include "automateFunc.h"
//Fonction qui permet de transformer le fichier en tableau
int fichierTotab(char *cheminFichier, char contenuFichier[TAILLE_MAX]) {
	FILE* fichier = fopen(cheminFichier, "r");
    int i = 0;
        if (fichier == NULL)
        {
            perror("fopen Error");
            return 1;
        }
        char tmp[TAILLE_MAX];
		while (fgets(tmp, TAILLE_MAX, fichier) != NULL) //stocker le fichier dans un tableau de char 
		{ 	
            strcat(contenuFichier,tmp);
            i++;
		}
		fclose(fichier);
        return 0;
}
//Fonction qui récupère le nombre d'Etat
int getNbEtats(char contenuFichier[TAILLE_MAX]){
    char endLine = '\n';
    const int cptLine = 3;
    int cpt = 0;

    for (size_t i = 0; i < strlen(contenuFichier); i++)
    {
        if (contenuFichier[i] == endLine){
            cpt++;
        }
        
    }

    return cpt-2;
}
//Fonction qui récupère l'Etat initial
int getEtatInitial(char contenuFichier[TAILLE_MAX]){
    char endLine = '\n';
    const int cptLine = 1;
    int cpt = 0;
    int result = 0;
    int drapeau = 0;

    for (size_t i = 0; i < strlen(contenuFichier); i++)
    {
        if (contenuFichier[i] == endLine && drapeau == 0){
            drapeau = 1;            
        } 
        if (drapeau == 1){
            result = contenuFichier[i+1] - '0';
            break;
        }
    }
        
    return result;
}
//Fonction qui récupère l'Etat final
int getEtatFinal(char contenuFichier[TAILLE_MAX]){
    char endLine = '\n';
    const int cptLine = 1;
    int cpt = 0;
    int result = 0;
    int drapeau = 0;

    for (size_t i = 0; i < strlen(contenuFichier); i++)
    {
        if (contenuFichier[i] == endLine && drapeau == 0){
            if (cpt == cptLine)
            {
               drapeau = 1; 
            }
            cpt++;                       
        }
        if (drapeau == 1){
            result = contenuFichier[i+1] - '0';
            break;
        }
    }
        
    return result;
}
//Fonction qui récupère le nombre de transition
int getNbTrans(int etat, char contenuFichier[TAILLE_MAX]) {
    char endLine, sep;
    endLine = '\n';
    sep = 59;

    int line, cptLine, cptTrans;
    line = etat + 3; //nb de lignes avant les infos sur les etats dans le fichier
    cptLine = 0;
    cptTrans = 0;
    
    for (size_t i = 0; i < strlen(contenuFichier); i++) {
        if(contenuFichier[i] == endLine) {
            cptLine++;
        }
        if(cptLine == line) {
            if(contenuFichier[i] == sep) {
                if(isalpha(contenuFichier[i-1])) {
                    cptTrans++;    
                }
            } 
            if (isalpha(contenuFichier[i])) {
                if(contenuFichier[i+1] != sep && !isalpha(contenuFichier[i+1])) {
                    cptTrans++;                    
                }
            }
        } 
        if(cptLine>line) {
            break;
        }
    }
    return cptTrans;
}
//Fonction qui récupère la taille de l'alphabet
int tailleAlphabet(char contenuFichier[TAILLE_MAX]){
    static char alphabet[TAILLE_MAX];
     char endLine = '\n';
    int i =0;
    while (contenuFichier[i] != endLine){
       alphabet[i] = contenuFichier[i];
       i++;
    }
    return strlen(alphabet);
}
//Fonction qui récupère l'alphabet'
char *getAlphabet(char contenuFichier[TAILLE_MAX]){
    static char alphabet[TAILLE_MAX];
    char endLine = '\n';
    int i =0;
    while (contenuFichier[i] != endLine){
       alphabet[i] = contenuFichier[i];
       i++;
    }
    return alphabet;
}