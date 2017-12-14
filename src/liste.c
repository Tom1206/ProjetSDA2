/**
* @file liste.c
* @brief Contient l'implémentation de la structure sous forme de liste chaînée
* @author Thomas Millot, Wael Hamed
* @version 1.0
* @date 15/12/2017
*/

#include "liste.h"


//@brief Créer un nouvel ensemble S ne contenant que l'élément p
//(p est le représentant de S)
Liste * MakeSet(Liste * e) {

    Representant * r = malloc(sizeof(Representant));

    e -> representant = r;
    r -> head = e;
    r -> tail = e;
    r -> taille = 1;

    return e;

}

//@brief Retourne un pointeur vers le représentant de l'ensemble contenant
//l'élément e
Representant * FindSet(Liste * e) {

    return e -> representant;

}

//@brief créer un nouvel ensemble S qui contient les éléments des ensembles A et B
//puis supprime les ensembles A et B
void Union(Liste * A, Liste * B) {

    // On teste si les deux ensembles sont disjoints
    if (FindSet(A) -> head != FindSet(B) -> head) {

        // Si A plus grand, on met B à la suite de A
        if (FindSet(A) -> taille > FindSet(B) -> taille) {

            FindSet(A) -> tail -> element_suivant = FindSet(B) -> head;
            FindSet(A) -> tail = FindSet(B) -> tail;
            FindSet(A) -> taille += FindSet(B) -> taille;

            Liste * courant = FindSet(B) -> head;

            while (courant != NULL) {

                courant -> representant = FindSet(A);

                courant = courant -> element_suivant;

            }

            // B devient A
            FindSet(B) -> head = FindSet(A) -> head;
            FindSet(B) -> tail = FindSet(A) -> tail;
            FindSet(B) -> taille = FindSet(A) -> taille;


        // Sinon on met A à la suite de B
        } else {

            FindSet(B) -> tail -> element_suivant = FindSet(A) -> head;
            FindSet(B) -> tail = FindSet(A) -> tail;
            FindSet(B) -> taille += FindSet(A) -> taille;

            Liste * courant = FindSet(A) -> head;

            while (courant != NULL) {

                courant -> representant = FindSet(B);

                courant = courant -> element_suivant;

            }

            // A devient B
            FindSet(A) -> head = FindSet(B) -> head;
            FindSet(A) -> tail = FindSet(B) -> tail;
            FindSet(A) -> taille = FindSet(B) -> taille;

        }

    }

}


Liste * nouvelElement (Pixel * P) {

    Liste * e = malloc(sizeof(Liste));

    e -> representant = NULL;
    e -> element_suivant = NULL;

    couleurAleatoire(P);
    e -> pixel = P;

    return e;

}


void coloriage(Image * I) {

    // initialisation de rand
    srand(time(NULL));

    // On crée un tableau de pointeurs sur listes, une liste par pixel
    Liste *** LL = malloc(I -> largeur * sizeof(Liste**));
    for (int i = 0; i < I -> largeur; i++) {
        LL[i] = malloc(I -> hauteur * sizeof(Liste*));
    }

    // On parcours cette liste
    for (int i = 0; i < I -> hauteur; i++) {
        for (int j = 0; j < I -> largeur; j++) {

            // On test si un pixel est noir
            if (I -> tableauPixels[j][i] -> R == 0 || I -> tableauPixels[j][i] -> G == 0 || I -> tableauPixels[j][i] -> B == 0) {

                // NULL signifiera la position d'un pixel noir
                LL[j][i] = NULL;

            } else {

                // On crée une nouvelle liste par pixel, avec une couleur aléatoire à chaque fois
                // La couleur est modififiée directment dans la structure image afin de gagner de la place mémoire
                LL[j][i] = MakeSet(nouvelElement(I -> tableauPixels[j][i]));

            }

        }
    }

    // On parcours à nouveau ce tableau de listes, cette fois-ci pour appliquer l'algo de coloriage
    for (int i = 0; i < I -> hauteur; i++) {
        for (int j = 0; j < I -> largeur; j++) {

            //traitement pixel supérieur
            if (LL[j][i] != NULL) {

                if (i > 0) {

                    if (LL[j][i - 1] != NULL) {

                        Union(LL[j][i], LL[j][i - 1]);

                    }
                }
            }

            //traitement pixel de gauche
            if (LL[j][i] != NULL) {

                if (j > 0) {

                    if (LL[j - 1][i] != NULL) {

                        Union(LL[j][i], LL[j - 1][i]);

                    }
                }
            }

            //traitement pixel de droite
            if (LL[j][i] != NULL) {

                if (j < I -> largeur - 1) {

                    if (LL[j + 1][i] != NULL) {

                        Union(LL[j][i], LL[j + 1][i]);

                    }
                }
            }


            //traitement pixel inférieur
            if (LL[j][i] != NULL) {

                if (i < I -> hauteur - 1) {

                    if (LL[j][i + 1] != NULL) {

                        Union(LL[j][i], LL[j][i + 1]);

                    }
                }
            }


        }
    }


    // Un boucle supplémentaire permet de récupérer la couleur de chaque ensemble
    for (int i = 0; i < I -> hauteur; i++) {

        for (int j = 0; j < I -> largeur; j++) {

            if (LL[j][i] != NULL) {

                I -> tableauPixels[j][i] = FindSet(LL[j][i]) -> head -> pixel;

            }
        }
    }

    //Finalement on libère la place mémoire
    for (int i = 0; i < I -> hauteur; i++) {
        for (int j = 0; j < I -> largeur; j++) {
            free(LL[j][i]);
        }
    }
    for (int i = 0; i < I -> largeur; i++) {
        free(LL[i]);
    }
    free(LL);

}


int main(int argc, char const *argv[]) {

    if (argc != 2) {
        return 1;
    }

    printf("Coloriage par liste\n");

    printf("Lecture du fichier .pbm\n");
    Image *I = Read((char *)argv[1]);

    printf("Coloriage de l'image\n");
    coloriage(I);

    printf("Écriture du fichier .ppm\n");
    Write(I, "test.ppm");

    printf("Supression de la structure image\n");
    supprimerImage(I);

    return 0;
}
