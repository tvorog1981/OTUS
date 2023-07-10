CC=gcc
FLAGS=-Wextra -Wpedantic

server:main.o
	$(CC) $(FLAGS) -o server main.o
main.o main.c
	$(CC) -c main.c
clean:
	rm -rf main.o server main.c~ config.file~
