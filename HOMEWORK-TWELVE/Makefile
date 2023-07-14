CC=gcc
FLAGS=-Wextra -Wpedantic -std=c11


hash:main.o
	$(CC) $(FLAGS) -o hash main.o
main.o: main.c
	$(CC) -c main.c
clean:
	rm -rf main.o hash *~
