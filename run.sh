
echo "* suppression /bin/liste\n"
rm ./bin/liste
echo "* make : "
make mrproper
make

echo "\n* execution ./bin/prog_test"
./bin/prog_test 
