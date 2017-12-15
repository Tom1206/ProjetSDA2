//programme qui test le traitement des images

#include "prog_test.h"
#include "arbre.c"


//@brief Génère des images aléatoires et les colorie afin de tester les temps d'éxecution
void benchmark(){
    printf("* Tests du temps d'éxecution des fonctions de coloriage *\n");
    int n = 10; //les images générées seront de taille n * n
    //on fait les tests pour n allant de 2 à n * 2^13
    for(int i = 1; i <= 13; i++){ 
        int taille = n * 2 * i;
        //on mesurera la moyenne du temps d'execution de 10 coloriages d'une image aléatoire de taille [taille * taille]
        for(int j = 0; j < 10; j++){
            char nom_image[512];
            sprintf(nom_image, "image_bench_%d_%d.pbm",taille, taille);
            printf(" - Génération d'une image aléatoire %s\n", nom_image);
            Generate(taille, taille, nom_image);
            //test du temps d'executuon avec la struct arbre
            Image *I = Read(nom_image);
            //TODO : début stopwatch
            coloriage(I);
            //TODO : fin stopwatch

            //TODO : ne pas enregistrer l'image (on veut tester les fonctions de coloriage, pas celles d'écriture dans un fichier)
            printf("Écriture du fichier .ppm\n");
            char image_res[512];
            sprintf(image_res,"image_bench_%d_%d.ppm",taille, taille);
            Write(I, image_res);

            printf("Supression de la structure image\n");
            supprimerImage(I);
        }
    }
}

void testFonctionGeneration(){
    Generate(10, 10, "generate.pbm");
}

int main(int argc, char** argv){

    (void)argc;(void)argv;
    printf("Prog_test\n");

    //Generate(10, 10, (char *)argv[1]);

    // printf("Lecture du fichier .pbm\n");
    // Image *I = Read((char *)argv[1]);
    //
    // printf("Écriture du fichier .ppm\n");
    // Write(I, "test.ppm");
    //
    // printf("Supression de la structure image\n");
    // supprimerImage(I);

    benchmark();

    //testFonctionGeneration();

    return 0;
}
