echo "* suppression /bin/liste\n"
rm ./bin/liste
echo "* make : "
make mrproper
make
echo "\n* execution ./bin/prog_test ./data/ImagesTests/petite_image_test.pbm"
./bin/prog_test ./data/ImagesTests/petite_image_test.pbm
echo "\n* gdb :"
#gdb ./bin/liste

echo "\n* execution ./bin/arbre "
./bin/arbre 