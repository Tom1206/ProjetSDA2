/**
* @file liste.h
* @brief Header for liste.c
* @author Thomas Millot, Wael Hamed
* @version 1.0
* @date 15/12/2017
*/

#ifndef LISTE_H
#define LISTE_H


#include "image.h"


//@brief Représente un des éléments de la liste chainée
typedef struct liste {

    Pixel *pixel;
    struct liste *element_suivant;
    struct representant *representant;

} Liste;


//@brief Représente la liste chainée de pixels
typedef struct representant {

    struct liste *head;
    struct liste *tail;
    int taille;

} Representant;


Liste * MakeSet(Liste * e);
Representant * FindSet(Liste * e);
void Union(Liste * A, Liste * B);
Liste * nouvelElement (Pixel * P);
void coloriage(Image * I);


#endif // LISTE_H
