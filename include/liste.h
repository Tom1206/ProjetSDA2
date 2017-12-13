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

#include "image.h" //juste pour récupérer la struct Pixel
//TODO (peut-être) : séparer le code de la struct dans un fichier .h à part

//@brief Représente un des éléments de la liste chainée
typedef struct element_liste {
    Pixel *pixel;
    struct element_liste *element_suivant;
    struct element_liste *representant;
} Element_liste;

//@brief Représente la liste chainée de pixels
typedef struct liste_pixels {
    struct element_liste *head;
    struct element_liste *tail;
} Liste_pixels;


#endif // LISTE_H
