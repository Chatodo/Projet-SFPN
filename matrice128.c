#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "matrice128.h"
#define bit128(M, l, c) (((c) < 64) ? ((M[l].lo >> (c)) & 1) : ((M[l].hi >> ((c)-64)) & 1))
#define flipbit128(M, l, c) (((c) < 64) ? (M[l].lo ^= ((uint64_t)1 << (c))) : (M[l].hi ^= ((uint64_t)1 << ((c)-64))))

void input_mat128(WORD128 mat[DIM]) {
    int l,c,val;
    for (l=0;l<DIM;l++) {
        mat[l].lo = 0;
        mat[l].hi = 0;
        for (c=0;c<DIM;c++) {
            if (c<DIM/2)
                val = 0;
            else
                val = 1;
            if (val) flipbit128(mat,l,c);
        }
    }
}

void print_mat128(WORD128 mat[DIM]) {
    int l,c;
    for (l=0;l<DIM;l++) {
        for (c=0;c<DIM;c++) {
            printf("%lu ",bit128(mat,l,c));
        }
        printf("\n");
    }
}

void init_zero128(WORD128 mat[DIM]) {
    int l;
    for (l=0;l<DIM;l++) {
        mat[l].lo = 0;
        mat[l].hi = 0;
    }
}