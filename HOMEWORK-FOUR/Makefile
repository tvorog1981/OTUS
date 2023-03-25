CC=clang
FLAGS=-Wpedantic -Wextra -std=c11 -Wall




main:main.o libparsing.so
	$(CC) $(FLAG) -o main main.o -L. -lparsing -Wl,-rpath,.

main.o:main.c
	$(CC) -c main.c

libparsing.so:parsing.o
	$(CC) $(FLAG) -shared  -o libparsing.so parsing.o

parsing.o:parsing.c
	$(CC) $(FLAG) -fPIC -c parsing.c

clean:
	rm -rf libparsing.so *.o main *.*~  *~  file.log
