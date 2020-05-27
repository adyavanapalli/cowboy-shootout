CC=gcc
CCFLAGS=-Wall -Wextra -Wpedantic
OPT=-O3

all: bin/cowboy-shootout

bin/cowboy-shootout: src/cowboy-shootout.c
	$(CC) $(CCFLAGS) $(OPT) src/cowboy-shootout.c -o bin/cowboy-shootout

clean:
	rm -f bin/*

.PHONY=all clean
