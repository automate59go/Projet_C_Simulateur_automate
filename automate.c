#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automateFunc.h"
#include "readFile.h"

char contenuFichier[TAILLE_MAX]; //contenant le contenu du fichier
char *cheminFichier; //variable contenant le chemin du fichier
char *motAverifier; //contenant le mot à verifier

int main(int argc, char *argv[]) {
	//On vérifie tout d'abord si tout est respecté dont le mot vide
	if (argc == 2)
	{
		cheminFichier = argv[1];
		fichierTotab(cheminFichier, contenuFichier);

		if(getEtatInitial(contenuFichier) == getEtatFinal(contenuFichier)){
			 printf("L'état %d est un etat initial et final\n",getEtatInitial(contenuFichier));
			 printf("Le mot vide a bien été reconnu ! \n");
			 return 0;
		}else{
			printf("Le mot vide n'est pas accepté par l'Automate ! \n");
			return 1;
		}

	}else if (argc < 3 || argc > 3) {
		printf("Nombre d'arguments incorrects !");
		return 1;
	}
	else {
		cheminFichier = argv[1]; //ici on stock les arguments 
		motAverifier = argv[2];
	}
	fichierTotab(cheminFichier, contenuFichier);
	//printf("%s", contenuFichier); //Affiche le contenu du fichier
	printf("Le mot a verifier est :  ");
	printf("\n");
	printf("%s", motAverifier); // Afficher le mot à Vérifier
	printf("\n");
	printf("Le nombre d'Etat :  ");
	printf("%d \n",getNbEtats(contenuFichier));
	printf("\n");
	printf("l'Etat initial :  ");
	printf("%d \n",getEtatInitial(contenuFichier));
	printf("\n");
	printf("l'Etat Final :  ");
	printf("%d \n",getEtatFinal(contenuFichier));
	printf("\n");
	printf("l'alphabet est : %s", getAlphabet(contenuFichier));
	printf("\n");

	Automate *autoM = create_automate(contenuFichier); //Creation de l'automate en fonction des infos du Fichier.
	//remplissage du tableau d'etats  
	for(int i = 0; i < getNbEtats(contenuFichier); i++) {
		if (i == getEtatFinal(contenuFichier)){
			autoM->etats[i] = *create_etat(i, 0, contenuFichier);
			aff_etat(&autoM->etats[i]);
		}
		else {
			autoM->etats[i] = *create_etat(i, 1, contenuFichier);
			aff_etat(&autoM->etats[i]);
		}
		make_trans(autoM, i, contenuFichier);
	}
	printf("\n");
	printf("Mot en vérification... \n");
	printf("\n");
	reconize_a_word(motAverifier,autoM,contenuFichier);

	return 0;
}