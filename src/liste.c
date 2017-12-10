/**
* @file liste.c
* @brief Contient l'implémentation de la structure sous forme de liste chaînée
* @author Thomas Millot, Wael Hamed
* @version 1.0
* @date 15/12/2017
*/

#include "liste.h"

/* code */

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
}

int main(int argc, char ** argv){
    (void)argc; (void)argv;
    tests_liste_pixel();
    return 1;
}

