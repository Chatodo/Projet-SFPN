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

void Transpose128(WORD128 transp[DIM], WORD128 mat[DIM]) {
    int l,l0,l1;
    WORD128 val1,val2;
    for (l = 0; l < DIM / 2; l++) {
        transp[l].lo = (mat[l].lo & 0xFFFFFFFF) | ((mat[l + (DIM / 2)].lo & 0xFFFFFFFF) << 32);
        transp[l].hi = (mat[l].hi & 0xFFFFFFFF) | ((mat[l + (DIM / 2)].hi & 0xFFFFFFFF) << 32);
        transp[l + (DIM / 2)].lo = (mat[l].lo >> 32) | (mat[l + (DIM / 2)].lo & 0xFFFFFFFF00000000);
        transp[l + (DIM / 2)].hi = (mat[l].hi >> 32) | (mat[l + (DIM / 2)].hi & 0xFFFFFFFF00000000);
    }
    for (l0 = 0; l0 < 2; l0++) {
        for (l1 = 0; l1 < DIM / 4; l1++) {
            l = l0 * (DIM / 2) + l1;
            val1.lo = (transp[l].lo & Cst64lo) | ((transp[l + (DIM / 4)].lo & Cst64lo) << 16);
            val1.hi = (transp[l].hi & Cst64hi) | ((transp[l + (DIM / 4)].hi & Cst64hi) << 16);
            val2.lo = ((transp[l].lo >> 16) & Cst64lo) | (transp[l + (DIM / 4)].lo & 0xFFFF0000FFFF0000);
            val2.hi = ((transp[l].hi >> 16) & Cst64hi) | (transp[l + (DIM / 4)].hi & 0xFFFF0000FFFF0000);
            transp[l].lo = val1.lo;
            transp[l].hi = val1.hi;
            transp[l + (DIM / 4)].lo = val2.lo;
            transp[l + (DIM / 4)].hi = val2.hi;
        }
    }
    for (l0 = 0; l0 < 4; l0++) {
        for (l1 = 0; l1 < DIM / 8; l1++) {
            l = l0 * (DIM / 4) + l1;
            val1.lo = (transp[l].lo & Cst32lo) | ((transp[l + (DIM / 8)].lo & Cst32lo) << 8);
            val1.hi = (transp[l].hi & Cst32hi) | ((transp[l + (DIM / 8)].hi & Cst32hi) << 8);
            val2.lo = ((transp[l].lo >> 8) & Cst32lo) | (transp[l + (DIM / 8)].lo & 0xFF00FF00FF00FF00);
            val2.hi = ((transp[l].hi >> 8) & Cst32hi) | (transp[l + (DIM / 8)].hi & 0xFF00FF00FF00FF00);
            transp[l].lo = val1.lo;
            transp[l].hi = val1.hi;
            transp[l + (DIM / 8)].lo = val2.lo;
            transp[l + (DIM / 8)].hi = val2.hi;
        }
    }

    for (l0 = 0; l0 < 8; l0++) {
        for (l1 = 0; l1 < DIM / 16; l1++) {
            l = l0 * (DIM / 8) + l1;
            val1.lo = (transp[l].lo & Cst16lo) | ((transp[l + (DIM / 16)].lo & Cst16lo) << 4);
            val1.hi = (transp[l].hi & Cst16hi) | ((transp[l + (DIM / 16)].hi & Cst16hi) << 4);
            val2.lo = ((transp[l].lo >> 4) & Cst16lo) | (transp[l + (DIM / 16)].lo & 0xF0F0F0F0F0F0F0F0);
            val2.hi = ((transp[l].hi >> 4) & Cst16hi) | (transp[l + (DIM / 16)].hi & 0xF0F0F0F0F0F0F0F0);
            transp[l].lo = val1.lo;
            transp[l].hi = val1.hi;
            transp[l + (DIM / 16)].lo = val2.lo;
            transp[l + (DIM / 16)].hi = val2.hi;
        }
    }

    for (l0 = 0; l0 < 16; l0++) {
         for (l1 = 0; l1 < DIM / 32; l1++) {
            l = l0 * (DIM / 16) + l1;
            val1.lo = (transp[l].lo & Cst8lo) | ((transp[l + (DIM / 32)].lo & Cst8lo) << 2);
            val1.hi = (transp[l].hi & Cst8hi) | ((transp[l + (DIM / 32)].hi & Cst8hi) << 2);
            val2.lo = ((transp[l].lo >> 2) & Cst8lo) | (transp[l + (DIM / 32)].lo & 0xCCCCCCCCCCCCCCCC);
            val2.hi = ((transp[l].hi >> 2) & Cst8hi) | (transp[l + (DIM / 32)].hi & 0xCCCCCCCCCCCCCCCC);
            transp[l].lo = val1.lo;
            transp[l].hi = val1.hi;
            transp[l + (DIM / 32)].lo = val2.lo;
            transp[l + (DIM / 32)].hi = val2.hi;
        }
    }

    for (l0 = 0; l0 < 32; l0++) {
        for (l1 = 0; l1 < DIM / 64; l1++) {
            l = l0 * (DIM / 32) + l1;
            val1.lo = (transp[l].lo & Cst4lo) | ((transp[l + (DIM / 64)].lo & Cst4lo) << 1);
            val1.hi = (transp[l].hi & Cst4hi) | ((transp[l + (DIM / 64)].hi & Cst4hi) << 1);
            val2.lo = ((transp[l].lo >> 1) & Cst4lo) | (transp[l + (DIM / 64)].lo & 0xAAAAAAAAAAAAAAAA);
            val2.hi = ((transp[l].hi >> 1) & Cst4hi) | (transp[l + (DIM / 64)].hi & 0xAAAAAAAAAAAAAAAA);
            transp[l].lo = val1.lo;
            transp[l].hi = val1.hi;
            transp[l + (DIM / 64)].lo = val2.lo;
            transp[l + (DIM / 64)].hi = val2.hi;
        }
    }

    for (l = 0; l < DIM; l += 2) {
        val1.lo = (transp[l].lo & Cst2lo) | ((transp[l + 1].lo & Cst2lo) << 1);
        val1.hi = (transp[l].hi & Cst2hi) | ((transp[l + 1].hi & Cst2hi) << 1);
        val2.lo = ((transp[l].lo >> 1) & Cst2lo) | (transp[l + 1].lo & 0x5555555555555555);
        val2.hi = ((transp[l].hi >> 1) & Cst2hi) | (transp[l + 1].hi & 0x5555555555555555);
         transp[l].lo = val1.lo;
        transp[l].hi = val1.hi;
        transp[l + 1].lo = val2.lo;
        transp[l + 1].hi = val2.hi;
    }
}

void matrice_1(WORD128 mat[DIM]) {
    for (int i = 0; i < DIM; i++) {
        mat[i].lo = 0xFFFFFFFFFFFFFFFF;
        mat[i].hi = 0xFFFFFFFFFFFFFFFF;
    }
}