/**
* @file liste.c
* @brief Contient l'implémentation de la structure sous forme de liste chaînée
* @author Thomas Millot, Wael Hamed
* @version 1.0
* @date 15/12/2017
*/

#include "liste.h"


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


void tests_liste_pixel(){
    //création d'un element Pixel qui sera le reprséentant de son ensemble
    Pixel *p = malloc(sizeof(Pixel));
    p->R = 1;
    p->G = 2;
    p->B = 3;

    Element_liste *e = malloc(sizeof(Element_liste));
    e->pixel = p;

    //création d'un nouvel ensemble depuis l'élément p
    Liste_pixels* liste = MakeSet(e);

    printf("r=%d, g=%d, b=%d\n",
        liste->head->pixel->R,
        liste->head->pixel->G,
        liste->tail->pixel->B //vérification que tail == head
        //(car l'ens. contient un seul elem)
    );

    liste->tail->pixel->B = 4; //vérification que head == tail
    printf("head->pixel->B = %d\n", liste->head->pixel->B);
    printf("head->element_suivant == NULL -> %d\n", liste->head->element_suivant == NULL);
    printf("head->representant == NULL -> %d\n", liste->head->representant == NULL);
}
