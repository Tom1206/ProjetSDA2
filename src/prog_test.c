//programme qui test le traitement des images

#include "prog_test.h"

int main(int argc, char** argv){

    (void)argc;
    printf("Prog_test\n");

    printf("Lecture du fichier .pbm\n");
    Image *I = Read((char *)argv[1]);

    printf("Écriture du fichier .ppm\n");
    Write(I, "test.ppm");

    printf("Supression de la structure image\n");
    supprimerImage(I);

    return 0;
}
