/**
* @file liste.h
* @brief Header for liste.c
* @author Thomas Millot, Wael Hammed
* @version 1.0
* @date 15/12/2017
*/

#ifndef LISTE_H
#define LISTE_H

#include <stdio.h>
#include <stdlib.h>

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


#endif // LISTE_H
