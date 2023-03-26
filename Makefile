CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -pedantic -O3
all: test1 test2 main1 main2
test1: clean
	$(CC) $(CFLAGS) -DM64 -c test_transpose.c -o test_transpose.o
	$(CC) $(CFLAGS) -DM64 -c matrice.c -o matrice.o
	$(CC) $(CFLAGS) -DM64 test_transpose.o matrice.o -o test1

test2: clean
	$(CC) $(CFLAGS) -DM128 -c test_transpose.c -o test_transpose.o
	$(CC) $(CFLAGS) -DM128 -c matrice.c -o matrice.o
	$(CC) $(CFLAGS) -DM128 test_transpose.o matrice.o -o test2

main1: clean
	$(CC) $(CFLAGS) -DM64 -c main.c -o main.o
	$(CC) $(CFLAGS) -DM64 -c matrice.c -o matrice.o
	$(CC) $(CFLAGS) -DM64 main.o matrice.o -o main1

main2: clean
	$(CC) $(CFLAGS) -DM128 -c main.c -o main.o
	$(CC) $(CFLAGS) -DM128 -c matrice.c -o matrice.o
	$(CC) $(CFLAGS) -DM128 main.o matrice.o -o main2
clean:
	rm -f *.o main[0-9] test[0-9]
