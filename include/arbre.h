/**
* @file arbre.h
* @brief Header for arbre.c
* @author Thomas Millot, Wael Hammed
* @version 1.0
* @date 15/12/2017
*/

#ifndef ARBRE_H
#define ARBRE_H

#include <stdio.h>
#include <stdlib.h>

#include "image.h" //juste pour récupérer la struct Pixel
//TODO (peut-être) : séparer le code de la struct dans un fichier .h à part

//@brief Représente un des noeuds
typedef struct noeud {
    Pixel *pixel;
    struct noeud *pere;
    int rang;
} Noeud;


#endif // ARBRE_H
