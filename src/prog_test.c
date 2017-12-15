//programme qui test le traitement des images

#include "prog_test.h"


int main(int argc, char** argv){

    (void)argc;(void)argv;
    printf("Prog_test\n");

    printf("Génération d'une image aléatoire\n");
    Generate(atoi(argv[2]), atoi(argv[3]), (char *)argv[1]);

    return 0;
}
