/**
* @file image.h
* @brief Header for image.c
* @author Thomas Millot, Wael Hammed
* @version 1.0
* @date 15/12/2017
*/

#ifndef IMAGE_H
#define IMAGE_H


#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <limits.h>


/**
* @struct pixel
* @brief Contient les trois couleurs composants un pixel
*/
typedef struct pixel {

    int R, G, B;

} Pixel;

/**
* @struct image
* @brief Contient un tableau de pixels et la taille de l'image
*/
typedef struct image {

    Pixel *** tableauPixels;
    int largeur, hauteur;

} Image;


Image * Read(char * nomImagePBM);
void Write(Image * image, char * nomImagePPM);
void couleurAleatoire(Pixel * P);
void Generate(int n, int m, char * nomImagePBM);
void supprimerImage(Image * image);
void enregistrerRes(char *nomFichier, int n, double temps);

#endif // IMAGE_H
