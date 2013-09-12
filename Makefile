CCOPTS = -c -I include -Wall -Wextra

all: bin/deviser

bin/deviser: obj/main.o obj/deviser.o
	gcc -o bin/deviser obj/main.o obj/deviser.o

obj/main.o: src/main.c include/deviser.h
	gcc ${CCOPTS} -o obj/main.o src/main.c

obj/deviser.o: src/deviser.c include/deviser.h
	gcc ${CCOPTS} -o obj/deviser.o src/deviser.c

.PHONY:clean
clean:
	rm -rf bin/* obj/*
