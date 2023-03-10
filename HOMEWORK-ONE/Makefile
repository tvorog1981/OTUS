CC=clang
FLAG= -Wall -Wextra -Wpedantic -std=c17

all:archiveZIP.exe 

archiveZIP.exe:zip.o
	$(CC) $(FLAG) -o archiveZIP.exe zip.o
zip.o:zip.c
	$(CC) -c zip.c

clean:
	rm -rf *.o  archiveZIP.exe
