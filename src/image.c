/**
* @file image.c
* @brief Contient toutes les fonctions nécessaire aux traitement des fichiers images
* @author Thomas Millot, Wael Hamed
* @version 1.0
* @date 15/12/2017
*/

#include "image.h"


/**
* @brief Lit un fichier PBM et stocke les pixels dans un tableau
* @param nomImagePBM Le fichier à ouvrir
* @return Un pointeur sur une structure image, contenant le tableau de pixels et la taille de l'image
*/
Image * Read(char * nomImagePBM) {


    Image * image = malloc(sizeof(Image));

    // On teste si le fichier existe
    if (access(nomImagePBM, F_OK) != 0) {
        printf("Le fichier \"%s\" n'existe pas\n", nomImagePBM);
        exit(EXIT_FAILURE);
    }

    struct stat stbuf;
    stat(nomImagePBM, &stbuf);

    // On teste s'il s'agit d'un fichier (et non pas d'un répertoire par exemple)
    if (S_ISREG (stbuf.st_mode)) {

        // On ouvre l'image
        int fd = open(nomImagePBM, O_RDONLY);
        if (fd == -1) {
            exit(EXIT_FAILURE);
        }

        // On charge dans la mémoire le contenu du fichier image
        char * contenuFichierImage;
        contenuFichierImage = (char *)mmap(NULL, stbuf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);


        // On teste la valeur du nombre magique, qui doit être "P1" ici
        if (contenuFichierImage[0] != 'P') {
            printf("L'image \"%s\" n'a pas le bon format\n", nomImagePBM);
            exit(EXIT_FAILURE);
        }
        if (contenuFichierImage[1] != '1') {
            printf("L'image \"%s\" n'a pas le bon format\n", nomImagePBM);
            exit(EXIT_FAILURE);
        }

        // On prépare une position dans le contenu de l'image
        int position = 3;

        char tmp[10];
        for (int i = 0; i < 10; i++) {
            tmp[i] = 0;
        }

        int compteur = 0;

        // On traite la largeur
        while (contenuFichierImage[position] != ' ') {
            tmp[compteur] = contenuFichierImage[position];
            compteur++;
            position++;
        }
        image -> largeur = atoi(tmp);

        compteur = 0;
        position++;

        // On remet tmp à 0
        for (int i = 0; i < 10; i++) {
            tmp[i] = 0;
        }

        // On traite la hauteur
        while (contenuFichierImage[position] != '\n') {
            tmp[compteur] = contenuFichierImage[position];
            compteur++;
            position++;
        }
        image -> hauteur = atoi(tmp);

        position++;

        // On peut maintenant allouer la mémoire nécessaire dans le tableau de pixels
        image -> tableauPixels = malloc(image -> largeur * sizeof(Pixel **));
        for (int i = 0; i < image -> largeur; i++) {
            image -> tableauPixels[i] = malloc(image -> hauteur * sizeof(Pixel *));
        }

        // On remplit ensuite les pixels du tableau

        int l = 0, h = 0;

        int taille = (int)strlen(contenuFichierImage);

        while (position < taille) {


            if (l == image -> largeur) {
                l = 0;
                h++;
            }

            // Cas saute de ligne
            if (contenuFichierImage[position] == '\n') {
                position++;
            }

            image -> tableauPixels[l][h] = malloc(sizeof(Pixel));

            // Cas pixel noir
            if (contenuFichierImage[position] == '1') {
                image -> tableauPixels[l][h] -> R = 0;
                image -> tableauPixels[l][h] -> G = 0;
                image -> tableauPixels[l][h] -> B = 0;
            }

            // Cas pixel blanc
            if (contenuFichierImage[position] == '0') {
                image -> tableauPixels[l][h] -> R = 255;
                image -> tableauPixels[l][h] -> G = 255;
                image -> tableauPixels[l][h] -> B = 255;
            }

            position++;
            l++;

        }

        // On ferme le file descriptor et on désalloue la mémoire
        if (close(fd) == -1) {
            exit(EXIT_FAILURE);
        }

        munmap(contenuFichierImage, stbuf.st_size);

    } else {
        printf("\"%s\" n'est pas un fichier, veuillez entrer un fichier valide\n", nomImagePBM);
        exit(EXIT_FAILURE);
    }

    return image;
}


void Write(Image * image, char * nomImagePPM) {

    // On crée l'introduction du fichier PPM
    char intro[100];
    sprintf(intro, "P3\n%d %d\n255\n", image -> largeur, image -> hauteur);

    // On alloue la place nécessaire au contenu du fichier :
    // la taille de l'introduction
    // + 4 caractères par couleur (3 digits + espace), 3 couleurs par pixel
    // + un peu plus d'espace au cas où
    char * contenuImage = malloc((strlen(intro) + (image -> largeur * image -> hauteur) * 3 * 4 * 2) * sizeof(char));

    // On écrit l'intro
    for (int i = 0; i < (int)strlen(intro); i++) {
        contenuImage[i] = intro[i];
    }

    int compteur = strlen(intro);

    // Tous les 5 pixels écrits, retour à la ligne
    int compteurPixels = 0;

    for (int i = 0; i < image -> hauteur; i++) {
        for (int j = 0; j < image -> largeur; j++) {

            // On test si on doit sauter une ligne
            if (compteurPixels == 5) {
                contenuImage[compteur] = '\n';
                compteur++;
                compteurPixels = 0;
            }

            // On formate les 3 couleurs du pixel
            char pixelAEcrire[15];
            sprintf(pixelAEcrire, "%d %d %d ", image -> tableauPixels[j][i] -> R, image -> tableauPixels[j][i] -> G, image -> tableauPixels[j][i] -> B);

            // Et on l'écrit à la suite du fichier
            int k = 0;
            while (pixelAEcrire[k] != '\0') {
                contenuImage[compteur] = pixelAEcrire[k];
                compteur++;
                k++;
            }

            compteurPixels++;

        }
    }

    // Finalement on écrit tout ça dans le fichier
    FILE *fichier = fopen(nomImagePPM, "w");

    if (fputs(contenuImage, fichier) == EOF) {
        exit(EXIT_FAILURE);
    }

    fclose(fichier);

}



void Generate(int n, int m, char * nomImagePBM) {


    // initialisation de rand
    srand(time(NULL));

    // On crée l'introduction du fichier PBM
    char intro[50];
    sprintf(intro, "P1\n%d %d\n", n, m);

    // On alloue la place nécessaire au contenu du fichier :
    // la taille de l'introduction
    // + 2 caractères par pixel (0 ou 1 + espace)
    // + un peu plus d'espace au cas où
    char * contenuImage = malloc((strlen(intro) + (n * m) * 3) * sizeof(char));

    // On écrit l'intro
    for (int i = 0; i < (int)strlen(intro); i++) {
        contenuImage[i] = intro[i];
    }

    int compteur = strlen(intro);

    int compteurPixels = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {

            // Tous les 35 pixels écrits, retour à la ligne
            if (compteurPixels == 35) {
                contenuImage[compteur] = '\n';
                compteur++;
                compteurPixels = 0;
            }

            // On met le pixel à 1 ou 0
            char pixelAEcrire[5];
            sprintf(pixelAEcrire, "%d ", rand()%2);

            // Et on l'écrit à la suite du contenu du fichier
            int k = 0;
            while (pixelAEcrire[k] != '\0') {
                contenuImage[compteur] = pixelAEcrire[k];
                compteur++;
                k++;
            }

            compteurPixels ++;

        }
    }

    // Finalement on écrit tout ça dans le fichier
    FILE *fichier = fopen(nomImagePBM, "w");

    if (fputs(contenuImage, fichier) == EOF) {
        exit(EXIT_FAILURE);
    }

    fclose(fichier);


}



void couleurAleatoire(Pixel * P) {


    // On alloue une valeur aléatoire à chaque composante couleur
    P->R = rand()%255;
    P->G = rand()%255;
    P->B = rand()%255;

    // Si la couleur crée est noire ou blanche, on recommence
    while ((P->R == 0 && P->G == 0 && P->B == 0) || (P->R == 255 && P->G == 255 && P->B == 255)) {
        P->R = rand()%255;
        P->G = rand()%255;
        P->B = rand()%255;
    }

}


void supprimerImage(Image * image) {

    for (int i = 0; i < image -> largeur; i++) {
        free(image -> tableauPixels[i]);
    }

    free(image -> tableauPixels);

    free(image);

}
