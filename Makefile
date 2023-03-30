CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -pedantic -O3
LIBS=-lpapi
all: test1 test2 main1 main2 bench
test1: clean
	$(CC) $(CFLAGS) -DM64 -c tests/test_transpose.c -o test_transpose.o
	$(CC) $(CFLAGS) -DM64 -c matrices/matrice.c -o matrice.o
	$(CC) $(CFLAGS) -DM64 test_transpose.o matrice.o -o test1

test2: clean
	$(CC) $(CFLAGS) -DM128 -c tests/test_transpose.c -o test_transpose.o
	$(CC) $(CFLAGS) -DM128 -c matrices/matrice.c -o matrice.o
	$(CC) $(CFLAGS) -DM128 test_transpose.o matrice.o -o test2

main1: clean
	$(CC) $(CFLAGS) -DM64 -c main.c -o main.o
	$(CC) $(CFLAGS) -DM64 -c matrices/matrice.c -o matrice.o
	$(CC) $(CFLAGS) -DM64 main.o matrice.o -o main1 $(LIBS)

main2: clean
	$(CC) $(CFLAGS) -DM128 -c main.c -o main.o
	$(CC) $(CFLAGS) -DM128 -c matrices/matrice.c -o matrice.o
	$(CC) $(CFLAGS) -DM128 main.o matrice.o -o main2 $(LIBS)

bench: clean
	$(CC) $(CFLAGS) -DM128 -c benchmarks/transpose_bench.c -o transpose_bench.o
	$(CC) $(CFLAGS) -DM128 -c matrices/matrice.c -o matrice.o
	$(CC) $(CFLAGS) -DM128 transpose_bench.o matrice.o -o bench $(LIBS)

clean:
	rm -f *.o main[0-9] test[0-9]
