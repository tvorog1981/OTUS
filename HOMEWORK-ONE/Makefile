CC=clang
FLAG= -Wall -Wextra -Wpedantic -std=c17

all:archiveZIP.exe archiveTAR.exe

archiveZIP.exe:zip.o
	$(CC) $(FLAG) -o archiveZIP.exe zip.o
zip.o:zip.c
	$(CC) -c zip.c
archiveTAR.exe:tar.o
	$(CC) $(FLAG) -o archiveTAR.exe tar.o
main.o: main.c
	$(CC) -c tar.c
clean:
	rm -rf *.o archiveTAR.exe archiveZIP.exe
