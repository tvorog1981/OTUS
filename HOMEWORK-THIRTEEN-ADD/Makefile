CC=gcc
FLAG=-Wextra -Wpedantic -std=c11


asm:list.o
	$(CC) $(FLAG) -o asm list.o
list.o:list.o
	$(CC) -c list.c
clean:
	rm -rf list.o asm *~
