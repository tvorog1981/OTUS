FLAG=-Wall -Wextra -Wpedantic -std=c11
LIB_CURL= -lcurl
LIB_JSON= -lcjson
CC=clang


json:curl.o
	$(CC) $(FLAG) $(LIB_CURL) $(LIB_JSON) -o json curl.o

curl.o:curl.c
	$(CC) -c curl.c
clean:
	rm -rf *.o *.*~ *~ json

