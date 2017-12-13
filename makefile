CC= gcc
CFLAGS= -W -Wall -g
LDFLAGS=
INCLUDES= -I "./include"
EXEC= bin/prog_test
SRC= $(wildcard src/*.c)
OBJ= $(patsubst src/%.c,obj/%.o,$(SRC))

all: $(EXEC)

bin/prog_test: obj/prog_test.o obj/image.o obj/liste.o
	$(CC) $(INCLUDES) -o $@ $^ $(LDFLAGS)

obj/%.o: src/%.c
	$(CC) $(INCLUDES) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf $(OBJ)

mrproper: clean
	rm -rf $(EXEC)
