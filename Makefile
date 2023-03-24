CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -pedantic -O3

main1: main.o matrice.o
	$(CC) $(CFLAGS) main.o matrice.o -o main1
main2: main.o matrice128.o
	$(CC) $(CFLAGS) main.o matrice128.o -o main2
test1: test_transpose.o matrice.o
	$(CC) $(CFLAGS) test_transpose.o matrice.o -o test1
test2: test_transpose.o matrice128.o
	$(CC) $(CFLAGS) test_transpose.o matrice.o -o test2
test_transpose.o: test_transpose.c matrice.h
	$(CC) $(CFLAGS) -c test_transpose.c -o test_transpose.o
main.o: main.c matrice128.h
	$(CC) $(CFLAGS) -c main.c -o main.o
matrice.o: matrice.c matrice.h
	$(CC) $(CFLAGS) -c matrice.c -o matrice.o
matrice128.o: matrice128.c matrice128.h
	$(CC) $(CFLAGS) -c matrice128.c -o matrice128.o
clean:
	rm -f *.o main test

.PHONY: main1 main2 test1 test2
main1: CFLAGS += -DTRANSPOSE1
main2: CFLAGS += -DTRANSPOSE2
test1: CFLAGS += -DTRANSPOSE1
test2: CFLAGS += -DTRANSPOSE2