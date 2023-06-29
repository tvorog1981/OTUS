#/bin/bash
rm -rf *.o otus *.c~ 
gcc -c  -I/usr/include/postgresql   main.c
gcc  -o otus main.o -lm -lpq -L/usr/lib
