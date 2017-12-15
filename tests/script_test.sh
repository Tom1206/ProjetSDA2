#!/bin/bash

echo "* Copie des programmes dans ce dossier *"
cp ../bin/* .
echo "* Génération de 10 images aléatoires n x n, avec n = { 1000 .. 10 000}. Coloriage de ces images *" 

#une seule image est générée et coloriée, pour d'abords tester que les prog fonctionnent
#./prog_test image_alea_nb_10_10.pbm 10 10
#./liste image_alea_nb_10_10.pbm #ne fonctionne pas -> l'image test.ppm n'est pas celle attendue !!!
#./liste carte_france.pbm

mkdir images
for (( c=1; c<=15; c++ ))
do 
    i=$((1000 * c ))

    echo "  - création d'une image aléatoire noir et blanc de taille $i x $i"
    ./prog_test images/image_alea_nb_$((i))_$((i)).pbm $((i)) $((i))
    
    echo "  - coloriage par ./liste :"
    ./liste images/image_alea_nb_$((i))_$((i)).pbm
    
    echo "  - coloriage par ./arbre :"
    ./arbre images/image_alea_nb_$((i))_$((i)).pbm
    
    echo " - suppression de l'image ppm (prend trop de place)"
    rm images/image_alea_nb_$((i))_$((i)).ppm
done

echo "* création d'un graphique (graphique.png) représentant les temps d'éxecution *"
./gnuplot_script.pg

echo "--> fin."