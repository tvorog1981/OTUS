CC=gcc
FLAGS=-Wextra -Wpedantic -std=c11


main:main.o 
	$(CC) $(FLAGS) -o main  main.o 
main.o:main.c
	$(CC) -c main.c
clean:
	rm -rf main.o make *~ crs32.o *.a
