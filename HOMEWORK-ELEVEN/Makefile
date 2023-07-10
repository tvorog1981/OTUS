CC=gcc
FLAGS=-Wextra -Wpedantic -std=c11

telnet:main.o
	$(CC) $(FLAGS) -o telent main.o
main.o:main.c
	$(CC) -c main.c
clean:
	rm -rf main.o telnet *~
