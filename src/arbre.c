/**
* @file arbre.c
* @brief Contient l'implémentation de la structure sous forme d'arbre
* @author Thomas Millot, Wael Hamed
* @version 1.0
* @date 15/12/2017
*/

#include "arbre.h"



//@brief Créer un nouvel ensemble S ne contenant que l'élément p
//(p est le représentant de S)
Noeud* MakeSet_arbre(Noeud *e){
    e->rang = 0;
    e->pere = e;
    return e;
}

int main(int argc, char** argv){
    (void)argc; (void)argv;
    printf("Hello arbre.c\n");
    return 1;
}