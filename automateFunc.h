#ifndef __AUTOMATE__
#define __AUTOMATE__
#include "readFile.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define UNDEFINED -1
#define EPSILON 0

typedef int bool;

//Définition des structures
typedef struct {
    char* symbol;
    int destination;
	int depart;
} Transition;

typedef struct {
	int n_etat;
    int nb_transitions;
    bool is_final;
    Transition* trans;
} Etat;

typedef struct {
    int nb_etats;
    int initial_etat;
    Etat* etats;
} Automate;

Automate* create_automate(char contenuFichier[TAILLE_MAX]);
Etat *create_etat(int n_etat, bool is_final,char contenuFichier[TAILLE_MAX]);
Transition* create_transition(char* symbol, int destinationEtat, int departEtat);
int add_etat(Automate *a, Etat * e);
void add_transition(Automate* a, int from, int to, char symbol[]);
bool has_etat(Automate* a, int etat);
void aff_automate(Automate * a);
void aff_etat(Etat *e);
void add_symbol(char symbol[], char s);
void make_trans(Automate *a,int etat, char contenuFichier[TAILLE_MAX]);
void reconize_a_word(char tab[],Automate * a,char contenuFichier[TAILLE_MAX]);

#endif