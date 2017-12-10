//programme qui test le traitement des images

#include "prog_test.h"

int main(int argc, char** argv){
    (void)argc;
    printf("Prog_test\n");

    printf("Lecture du fichier .pbm\n");
    Image *I = Read((char *)argv[1]);
    (void)I;
    return 1;
}