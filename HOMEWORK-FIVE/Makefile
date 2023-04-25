CC=clang
FLAG=-Wpedantic -Wextra -std=c11



sock_stream:main.o
	$(CC) $(FLAG) -o sock_stream main.o
main.o:main.c
	$(CC) -c main.c
clean:
	rm -rf *.o *~ sock_stream
