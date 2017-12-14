/**
* @file arbre.h
* @brief Header for arbre.c
* @author Thomas Millot, Wael Hammed
* @version 1.0
* @date 15/12/2017
*/

#ifndef ARBRE_H
#define ARBRE_H


#include "image.h"


//@brief Représente un des noeuds
typedef struct noeud {

    Pixel *pixel;
    struct noeud *pere;
    int rang;

} Noeud;


Noeud* MakeSet(Noeud *e);
Noeud* FindSet(Noeud *e);
void Union(Noeud *x, Noeud *y);
Noeud* nouvelElement (Pixel * P);
void coloriage(Image * I);


#endif // ARBRE_H
