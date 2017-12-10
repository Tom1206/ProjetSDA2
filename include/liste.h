/**
* @file liste.h
* @brief Header for liste.c
* @author Thomas Millot, Wael Hammed
* @version 1.0
* @date 15/12/2017
*/

//TODO : déplacer le corps des fonctions dans liste.c

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
    res->head->representant = e;
    res->tail = res->head;
    return res;
}

//@brief Retourne un pointeur vers le représentant de l'ensemble contenant
//l'élément e
Element_liste* FindSet(Element_liste *e){
    return e->representant;
}

//@brief créer un nouvel ensemble S qui contient les éléments des ensembles A et B
//puis supprime les ensembles A et B
//@pre Les ens. A et B doivent être disjoints
Liste_pixels* Union(Liste_pixels *A, Liste_pixels *B){
    Liste_pixels *res = init_list();
    
    //si les ens. A et B sont vides on renvoit un nouvel ens. vide
    if(A->head == NULL && B->head == NULL){
        printf("Warning : Union() -> Ensembles A et B vides.\n");
        return res;
    }
    Element_liste *elem_courant = res->head;
    Element_liste *e = malloc(sizeof(Element_liste));
    e = A->head;
    while(e != NULL){
        elem_courant = e;
        elem_courant = elem_courant->element_suivant;
        e = e->element_suivant;
    }

    e = B->head;
    while(e != NULL){
        elem_courant = e;
        elem_courant = elem_courant->element_suivant;
        e = e->element_suivant;
    }
    free(A);
    free(B);
    return res;
}

#endif // LISTE_H
