#include "automateFunc.h"

//Creation de l'automate
Automate * create_automate(char contenuFichier[TAILLE_MAX]) {
	Automate * a = malloc(sizeof(Automate));
	a->nb_etats = getNbEtats(contenuFichier);
	a->initial_etat = getEtatInitial(contenuFichier);
	a->etats = malloc(a->nb_etats*sizeof(Etat));
	return a;
}
//Fonction qui affiche un automate
void aff_automate(Automate * a){
    printf("nombre d'etat : %d | etat initial : %d\n", a->nb_etats,a->initial_etat);
}

//Creation de l'Etat
Etat * create_etat(int n_etat, bool is_final,char contenuFichier[TAILLE_MAX]) {
	Etat * e = malloc(sizeof(Etat));
	e->n_etat = n_etat;
	e->nb_transitions = getNbTrans(n_etat, contenuFichier);
	e->is_final = is_final;
	e->trans = malloc(100*sizeof(Transition));
	return e;	
}
//Fonction qui affiche un Etat
void aff_etat(Etat * e){
   printf("numero de l'Etat : %d | nb de transition : %d\n", e->n_etat,e->nb_transitions);
}
//Creation d'une transition
Transition * create_transition(char symbol[], int destinationEtat, int departEtat) {
	Transition *t = malloc(sizeof(Transition));
    t->symbol =malloc(100*sizeof(char)) ;
    strcpy(t->symbol,symbol);
	t->destination = destinationEtat;
    t->depart = departEtat;
	return t;
}

//permet d'ajouter un Etat à un automate donné
int add_etat(Automate *a, Etat *e) {
    int res = 0;
    static int cptEtat = 0;
	if(has_etat(a, e->n_etat) == TRUE || cptEtat > sizeof(a->etats)) {
		res = 1;
		return res; 
	}
        
	a->etats[cptEtat] = *e;
    cptEtat++;
	return res;
}

//Verifier si l'etat donné en param existe dans le tableau des etats
bool has_etat(Automate * a, int etat) {
	bool res = FALSE;
	for (int i = 0; i < sizeof (a->etats); i++) {
		if (a->etats[i].n_etat == etat)
			res = TRUE;
	}
	return res;
}
//Ajouter une transition 
void add_transition(Automate* a, int from, int to, char symbol[]) {
    static int cptTrans = 0;
    if (cptTrans == a->nb_etats)
    {
        cptTrans = 0;
    }
		a->etats[from].trans[cptTrans] = *create_transition(symbol, to, from);
        cptTrans++;	
}

//fonction qui permet de déterminer si un etat est finale
bool is_final(int etat, char contenuFichier[TAILLE_MAX]){
    int etatFinal = getEtatFinal(contenuFichier);
    if (etatFinal == etat)
    {
        return TRUE;
    }
    return FALSE;
}
//Fonction qui permet d'ajouter un symbol à un tableau
void add_symbol(char symbol[], char s) {
    //printf("y a t'il des parenthèses ? : %s\n",symbol);
    for(int i = 0; i < strlen(symbol); i++) {
        if (!isalpha(symbol[i])){
            symbol[i] = s; 
            //printf("y a t'il des parenthèses ? : %s\n",symbol);
            break;
        }
    }
}
//Fonction utilitaire qui permet d'initialiser' un tableau
void initTab(char tab[]){
     for(int i = 0; i < strlen(tab); i++) {
            tab[i] = ' '; 
    }
}
//Fonction utilitaire qui permet de reset un tableau
void resetTab(char symbol[]){
      for(int i = 0; i < strlen(symbol); i++) {
            symbol[i] = ' '; 
    }
}
//Fonction qui permet d'initialiser les transition
void make_trans(Automate *a, int etat, char contenuFichier[TAILLE_MAX]) {
    char endLine, sep;
    int line, to, cptLine;

    endLine = 10;
    sep = 59;
    cptLine = 0;
    line = etat + 3;
    to = 0;
    char symbol[] ="aaaaaaaaaa";
    initTab(symbol);
    
    if (getNbTrans(etat, contenuFichier) <= 0) {
        printf("\n");
        printf("L'etat %d ne permets pas de transitions possibles !", etat);
        printf("\n");
    } else {
         
        for (size_t i = 0; i < strlen(contenuFichier); i++) {
            
            if(contenuFichier[i] == endLine) {
                cptLine++;
            }

            if(cptLine == line) {    
                if(isalpha(contenuFichier[i])) {
                    add_symbol(symbol, contenuFichier[i]);
                } else if(contenuFichier[i] == sep || contenuFichier[i+1] == endLine) {
                    add_transition(a, etat, to, symbol);
                    resetTab(symbol);
                    to++;
                }
            }

            if(cptLine>line) {
                break;
            }
        }
    }
}
//Fonction utilitaire qui permet de savoir si un caractère est dans un tableau
bool is_in_tab(char s, char tab[]){
    for (size_t i = 0; i < strlen(tab); i++){
            if (tab[i] == s){
                return TRUE;
            }
    }
    return FALSE;
}
//Fonction qui permet de déterminer si un mot est accepté
void reconize_a_word(char tab[],Automate * a,char contenuFichier[TAILLE_MAX]){
    int etat_courant = a->initial_etat;
    
    for (size_t i = 0; i < strlen(tab); i++){
        char char_courant = tab[i];

        if (is_in_tab(char_courant,getAlphabet(contenuFichier)) == FALSE)
        {
            printf("La caractère %c n'est pas contenue dans l'Alphabet !\n",char_courant);
            printf("Le mot est irrecevable par l'Automate ! \n");
            exit(1);
        }
        for (size_t j = 0; j < a->nb_etats; j++){
            if (is_in_tab(char_courant,a->etats[etat_courant].trans[j].symbol) == TRUE){
                printf("%d - %c -> %d\n",etat_courant,char_courant,a->etats[etat_courant].trans[j].destination);
                etat_courant = a->etats[etat_courant].trans[j].destination;
                break;
            }
        }
    }
    if (is_final(etat_courant,contenuFichier) == TRUE){
        printf("\n");
        printf("L'état %d est un etat final\n",etat_courant);
        printf("Le mot a bien été reconnu ! \n");
        printf("\n");
    }else{
        printf("\n");
        printf("L'état %d n'est pas un état final\n",etat_courant);
        printf("Le mot n'est pas accepté par l'Automate ! \n");
        printf("\n");
    }
}