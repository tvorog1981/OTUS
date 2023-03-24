CC=clang
FLAGS=-Wpedantic -Wextra -std=c11


decoder:decoder.o
	$(CC) $(FLAG) -o decoder decoder.o

decoder.o:decoder.c encoding.h
	$(CC) -c decoder.c
clean:
	rm -rf *.o decoder *~
