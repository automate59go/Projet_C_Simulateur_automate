# Projet C : simulateur d'automates
### réalisé par Kharmach Amine et Deroubaix François
[Liens vers le sujet](https://www.iut-info.univ-lille.fr/~lhoussai/C/projet/sujet.html)
# Focntionnement

## Description :

Ce programme permet de simuler la lecture d'un mot par un automate déterministe avec un nombre d'Etat quelconque.
</br>
Le mot vide est aussi simulé si vous ne mettez aucun argument à la place de la zone du mot (voir § Exécution).

## Compilation :

Pour compiler le programme :

>Sous linux et MacOS : make

>Sous Windows(avec MinGW) : mingw32-make

---

## Exécution

>Sous linux et MacOS : ./automate <Votre fichier> [<le mot à vérifer> | ou vide pour simuler le mot vide]

>Sous Windows(avec MinGW) : automate.exe <Votre fichier> [<le mot à vérifer> | ou vide pour simuler le mot vide]

## Syntax du fichier de définition
```
abc
0
2
bc;a;;
c;a;b;
;;abc;
```

## Organisation du projet

Le projet est séparé en 3 partie :

1. automate.c -> regroupe le main du programme et son déroulement
2. readFile.c -> regroupe toute les fonctions de lecture du fichier et l'initialisation des différentes strutures
3. automateFunc.c -> regroupe toutes les fonctions de traitement de l'automate

