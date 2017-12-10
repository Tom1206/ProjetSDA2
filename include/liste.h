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

//@brief Initialise une liste de pixels vide
//@return Pointeur vers la struct représentant une liste de pixels
Liste_pixels* init_list(){
    Liste_pixels* res = malloc(sizeof(Liste_pixels));
    res->head = malloc(sizeof(Element_liste));
    res->tail = malloc(sizeof(Element_liste));
    return res;
}


//@brief Créer un nouvel ensemble S ne contenant que l'élément p
//(p est le représentant de S)
Liste_pixels* MakeSet(Element_liste *e){
    Liste_pixels *res = init_list();
    res->head = e;
    res->tail = res->head;
    return res;
}

#endif // LISTE_H
