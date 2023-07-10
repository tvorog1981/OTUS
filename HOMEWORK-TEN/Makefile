CC=gcc
FLAGS=-Wextra -Wpedantic -std=c11

all: rfc32

rfc32: main.o
	$(CC) $(FLAGS) -o rfc32  main.o
main.o: main.c
	$(CC) -c main.c
clean:
	rm -rf main.o *~ rfc
