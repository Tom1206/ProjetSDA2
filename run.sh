echo "* suppression /bin/liste\n"
rm ./bin/liste
echo "* make : "
make
echo "\n* execution ./bin/liste"
./bin/liste
echo "\n* gdb :"
#gdb ./bin/liste
