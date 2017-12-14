CC= gcc
CFLAGS= -W -Wall -g
LDFLAGS=
INCLUDES= -I "./include"
EXEC= bin/liste bin/prog_test
SRC= $(wildcard src/*.c)
OBJ= $(patsubst src/%.c,obj/%.o,$(SRC))

all: $(EXEC)

bin/liste: obj/image.o obj/liste.o
	$(CC) $(INCLUDES) -o $@ $^ $(LDFLAGS)

bin/prog_test: obj/image.o obj/prog_test.o
	$(CC) $(INCLUDES) -o $@ $^ $(LDFLAGS)

#bin/arbre: obj/arbre.o obj/image.o
#	$(CC) $(INCLUDES) -o $@ $^ $(LDFLAGS)

obj/%.o: src/%.c
	$(CC) $(INCLUDES) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf $(OBJ)

mrproper: clean
	rm -rf $(EXEC)
