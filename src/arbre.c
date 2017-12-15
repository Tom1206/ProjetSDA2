/**
* @file arbre.c
* @brief Contient l'implémentation de la structure sous forme d'arbre
* @author Thomas Millot, Wael Hamed
* @version 1.0
* @date 15/12/2017
*/

#include "arbre.h"

//@brief Créer un nouvel ensemble S ne contenant que l'élément p
//(p est le représentant de S)
Noeud* MakeSet(Noeud *e){

    e->rang = 0;
    e->pere = e;

    return e;

}

//@brief Retourne un poiteur vers le représentant de l'ensemble contenant l'élément e
Noeud* FindSet(Noeud *e) {

    Noeud *res = e;

    // Tant qu'on est pas sur la racine
    while(res->pere != res){
        res = res->pere;
    }

    return res;

}

//@brief Créer un nouvel arbre S contenant à la fois les
//élém. de l'arbre A (contenant x) et les éléments de l'arbre B (contenant y)
void Union(Noeud *x, Noeud *y){

    Noeud *A = FindSet(x);
    Noeud *B = FindSet(y);

    //le rang de l'ensemble S sera le rang de la racine du long arbre +1
    int rang = A->rang >= B->rang ? A->rang : B->rang;
    rang++;

    A->rang = rang;

    //on relie la racine de l'arbre B à celle de l'arbre A
    //(racine de B devient un fils de la racine de A)
    B->pere = A;

}

//@brief Créer un nouveau Noeud (racine d'un nouvel arbre) à partir d'un Pixel
Noeud* nouvelElement (Pixel * P) {

    Noeud *e = malloc(sizeof(Noeud));

    e -> pere = e;
    e -> rang = 0;

    couleurAleatoire(P);
    e -> pixel = P;

    return e;

}

void coloriage(Image * I) {

    // initialisation de rand
    srand(time(NULL));

    // On crée un tableau de pointeurs sur Noeud, un arbre par pixel
    Noeud *** NN = malloc(I -> largeur * sizeof(Noeud**));
    for (int i = 0; i < I -> largeur; i++) {
        NN[i] = malloc(I -> hauteur * sizeof(Noeud*));
    }

    // On parcours ce tableau
    for (int i = 0; i < I -> hauteur; i++) {
        for (int j = 0; j < I -> largeur; j++) {

            // Si le pixel est noir
            if (I -> tableauPixels[j][i] -> R == 0 || I -> tableauPixels[j][i] -> G == 0 || I -> tableauPixels[j][i] -> B == 0) {

                // NULL signifiera la position d'un pixel noir
                NN[j][i] = NULL;

            } else {

                // On crée un nouveau Noeud par pixel, avec une couleur aléatoire à chaque fois
                // La couleur est modififiée directment dans la structure image afin de gagner de la place mémoire
                NN[j][i] = MakeSet(nouvelElement(I -> tableauPixels[j][i]));

            }

        }
    }

    // On parcours ce tableau de listes
    for (int i = 0; i < I -> hauteur; i++) {
        for (int j = 0; j < I -> largeur; j++) {

            //traitement pixel supérieur
            if (NN[j][i] != NULL) {

                if (i > 0) {

                    if (NN[j][i - 1] != NULL) {

                        Union(NN[j][i], NN[j][i - 1]);

                    }
                }
            }

            //traitement pixel de gauche
            if (NN[j][i] != NULL) {

                if (j > 0) {

                    if (NN[j - 1][i] != NULL) {

                        Union(NN[j][i], NN[j - 1][i]);

                    }
                }
            }

            //traitement pixel de droite
            if (NN[j][i] != NULL) {

                if (j < I -> largeur - 1) {

                    if (NN[j + 1][i] != NULL) {

                        Union(NN[j][i], NN[j + 1][i]);

                    }
                }
            }


            //traitement pixel inférieur
            if (NN[j][i] != NULL) {

                if (i < I -> hauteur - 1) {

                    if (NN[j][i + 1] != NULL) {

                        Union(NN[j][i], NN[j][i + 1]);

                    }
                }
            }


        }
    }


    // Un boucle supplémentaire permet de récupérer la couleur de chaque ensemble
    for (int i = 0; i < I -> hauteur; i++) {

        for (int j = 0; j < I -> largeur; j++) {

            if (NN[j][i] != NULL) {

                I -> tableauPixels[j][i] = FindSet(NN[j][i]) -> pixel;

            }
        }
    }

    //Finalement on libère la place mémoire
    for (int i = 0; i < I -> hauteur; i++) {
        for (int j = 0; j < I -> largeur; j++) {
            free(NN[j][i]);
        }
    }
    for (int i = 0; i < I -> largeur; i++) {
        free(NN[i]);
    }
    free(NN);

}


int main(int argc, char const *argv[]) {

    if (argc != 2) {
        return 1;
    }

    printf("Coloriage par arbre\n");

    printf("Lecture du fichier .pbm\n");
    Image *I = Read((char *)argv[1]);

    //début du chrono
	clock_t chrono;
    chrono = clock();

    printf("Coloriage de l'image\n");
    coloriage(I);

    //fin du chrono
	chrono = clock() - chrono;
	double time_taken = ((double)chrono)/CLOCKS_PER_SEC; // en secondes
	printf("(n=%d, m=%d, temps exec: %f s)\n\n",I->hauteur, I->largeur,time_taken);
    //enregistrement du temps d'execution dans un fichier txt
    enregistrerRes("temps_exec_arbre.txt",I->largeur,time_taken);
    //petite manipulation de chaîne pour avoir le nom du fichier .pbm
    char *nom_fichier_res = (char*)argv[1];
    int str_len = strlen(nom_fichier_res);
    nom_fichier_res[str_len -2] = 'p';
    //enregistrement de la version coloriée
    int ENREGISTRER_IMAGE_PPM = 0;
    if(ENREGISTRER_IMAGE_PPM == 1){
        printf("Écriture du fichier .ppm\n");
        Write(I, nom_fichier_res);
    }

    printf("Supression de la structure image\n");
    supprimerImage(I);

    return 0;
}
