CC=clang
FLAG= -Wall -Wextra -Wpedantic -std=c17




archive.exe:main.o
	$(CC) $(FLAG) -o archive main.o
main.o: main.c
	$(CC) -c main.c
clean:
	rm -rf *.o archive
