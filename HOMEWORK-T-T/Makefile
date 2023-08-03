CC=gcc
FLAGS=-Wextra -Wpedantic -std=c99



server:main.o
	$(CC) -o server $(FLAGS) main.o
main.o:main.c
	$(CC) -c main.c
clear:
	rm -rf *.o server *~
