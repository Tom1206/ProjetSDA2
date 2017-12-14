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
Noeud* MakeSet(Noeud *e){
    e->rang = 0;
    e->pere = e;
    return e;
}

//@brief Retourne un poiteur vers le représentant de l'ensemble contenant l'élément e
Noeud* FindSet(Noeud *e){
    Noeud *res = e;
    //tant qu'on est pas sur la racine
    while(res->pere != res){
        res = res->pere;
    }
    return res;
}

//@brief Créer un nouvel arbre S contenant à la fois les 
//élém. de l'arbre A (contenant x) et les éléments de l'arbre B (contenant y)
Noeud* Union(Noeud *x, Noeud *y){
    Noeud *A = FindSet(x);
    Noeud *B = FindSet(y);
    //le rang de l'ensemble S sera le rang de la racine du long arbre +1
    int rang = A->rang >= B->rang ? A->rang : B->rang;
    rang++;
    A->rang = rang;
    //on relie la racine de l'arbre B à celle de l'arbre A 
    //(racine de B devient un fils de la racine de A)
    B->pere = A;

    return A;
}

//@brief Créer un nouveau Noeud (racine d'un nouvel arbre) depuis un Pixel
Noeud* nouvelElement (Pixel * P) {
    Noeud *e = malloc(sizeof(Noeud));
    e -> pere = e;
    e -> rang = 0;
    couleurAleatoire(P);
    e -> pixel = P;
    return e;
}

int main(int argc, char** argv){
    (void)argc; (void)argv;
    printf("Hello arbre.c\n");
    return 1;
}