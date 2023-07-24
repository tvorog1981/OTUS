CC=gcc


asm: main.o
	$(CC) $(CFLAGS) main.o -o asm
main.o: main.c
	$(CC) -c main.c
clean:
	rm -rf main.o asm *~
