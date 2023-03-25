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


//Une autre façon de faire la transposition

// int getbit(WORD128 mat[DIM], int l, int c) {
//     int bit_index = c % 64;
//     WORD word = (c < 64) ? mat[l].lo : mat[l].hi;
//     return (word >> bit_index) & 1;
// }

// void setbit(WORD128 mat[DIM], int l, int c, int value) {
//     int bit_index = c % 64;
//     if (value) {
//         if (c < 64) {
//             mat[l].lo |= (WORD)1 << bit_index;
//         } else {
//             mat[l].hi |= (WORD)1 << bit_index;
//         }
//     } else {
//         if (c < 64) {
//             mat[l].lo &= ~((WORD)1 << bit_index);
//         } else {
//             mat[l].hi &= ~((WORD)1 << bit_index);
//         }
//     }
// }

// void Transpose128(WORD128 transp[DIM], WORD128 mat[DIM]) {
//     int l, c;
//     for (l = 0; l < DIM; l++) {
//         for (c = 0; c < DIM; c++) {
//             if (l != c) {
//                 int bit_l_c = getbit(mat, l, c);
//                 int bit_c_l = getbit(mat, c, l);
//                 setbit(transp, l, c, bit_c_l);
//                 setbit(transp, c, l, bit_l_c);
//             } else {
//                 int bit_l_c = getbit(mat, l, c);
//                 setbit(transp, l, c, bit_l_c);
//             }
//         }
//     }
// }

void Transpose128(word128 transp[DIM], word128 mat[DIM]) {
    int l, l0, l1;
    WORD val1_lo, val1_hi, val2_lo, val2_hi;

    for (l = 0; l < DIM; l++) {
        transp[l].lo = (mat[l].lo & Cst32) | ((mat[l].hi & Cst32) << 32);
        transp[l].hi = ((mat[l].lo >> 32) & Cst32) | (mat[l].hi & (Cst32 << 32));
    }

    for (l0 = 0; l0 < 2; l0++) {
        for (l1 = 0; l1 < DIM / 4; l1++) {
            l = l0 * (DIM / 2) + l1;
            val1_lo = (transp[l].lo & Cst16) | ((transp[l + (DIM / 4)].lo & Cst16) << 16);
            val1_hi = (transp[l].hi & Cst16) | ((transp[l + (DIM / 4)].hi & Cst16) << 16);
            val2_lo = ((transp[l].lo >> 16) & Cst16) | (transp[l + (DIM / 4)].lo & (Cst16 << 16));
            val2_hi = ((transp[l].hi >> 16) & Cst16) | (transp[l + (DIM / 4)].hi & (Cst16 << 16));
            transp[l].lo = val1_lo;
            transp[l].hi = val1_hi;
            transp[l + (DIM / 4)].lo = val2_lo;
            transp[l + (DIM / 4)].hi = val2_hi;
        }
    }

    for (l0 = 0; l0 < 4; l0++) {
        for (l1 = 0; l1 < DIM / 8; l1++) {
            l = l0 * (DIM / 4) + l1;
            val1_lo = (transp[l].lo & Cst8) | ((transp[l + (DIM / 8)].lo & Cst8) << 8);
            val1_hi = (transp[l].hi & Cst8) | ((transp[l + (DIM / 8)].hi & Cst8) << 8);
            val2_lo = ((transp[l].lo >>8) & Cst8) | (transp[l + (DIM / 8)].lo & (Cst8 << 8));
            val2_hi = ((transp[l].hi >> 8) & Cst8) | (transp[l + (DIM / 8)].hi & (Cst8 << 8));
            transp[l].lo = val1_lo;
            transp[l].hi = val1_hi;
            transp[l + (DIM / 8)].lo = val2_lo;
            transp[l + (DIM / 8)].hi = val2_hi;
        }
    }

    for (l0 = 0; l0 < 8; l0++) {
        for (l1 = 0; l1 < DIM / 16; l1++) {
            l = l0 * (DIM / 8) + l1;
            val1_lo = (transp[l].lo & Cst4) | ((transp[l + (DIM / 16)].lo & Cst4) << 4);
            val1_hi = (transp[l].hi & Cst4) | ((transp[l + (DIM / 16)].hi & Cst4) << 4);
            val2_lo = ((transp[l].lo >> 4) & Cst4) | (transp[l + (DIM / 16)].lo & (Cst4 << 4));
            val2_hi = ((transp[l].hi >> 4) & Cst4) | (transp[l + (DIM / 16)].hi & (Cst4 << 4));
            transp[l].lo = val1_lo;
            transp[l].hi = val1_hi;
            transp[l + (DIM / 16)].lo = val2_lo;
            transp[l + (DIM / 16)].hi = val2_hi;
            }
    }

    for (l0 = 0; l0 < 16; l0++) {
        for (l1 = 0; l1 < DIM / 32; l1++) {
            l = l0 * (DIM / 16) + l1;
            val1_lo = (transp[l].lo & Cst2) | ((transp[l + (DIM / 32)].lo & Cst2) << 2);
            val1_hi = (transp[l].hi & Cst2) | ((transp[l + (DIM / 32)].hi & Cst2) << 2);
            val2_lo = ((transp[l].lo >> 2) & Cst2) | (transp[l + (DIM / 32)].lo & (Cst2 << 2));
            val2_hi = ((transp[l].hi >> 2) & Cst2) | (transp[l + (DIM / 32)].hi & (Cst2 << 2));
            transp[l].lo = val1_lo;
            transp[l].hi = val1_hi;
            transp[l + (DIM / 32)].lo = val2_lo;
            transp[l + (DIM / 32)].hi = val2_hi;
        }
    }

    for (l0 = 0; l0 < 32; l0++) {
        for (l1 = 0; l1 < DIM / 64; l1++) {
            l = l0 * (DIM / 32) + l1;
            val1_lo = (transp[l].lo & Cst1) | ((transp[l + (DIM / 64)].lo & Cst1) << 1);
            val1_hi = (transp[l].hi & Cst1) | ((transp[l + (DIM / 64)].hi & Cst1) << 1);
            val2_lo = ((transp[l].lo >> 1) & Cst1) | (transp[l + (DIM / 64)].lo & (Cst1 << 1));
            val2_hi = ((transp[l].hi >> 1) & Cst1) | (transp[l + (DIM / 64)].hi & (Cst1 << 1));
            transp[l].lo = val1_lo;
            transp[l].hi = val1_hi;
            transp[l + (DIM / 64)].lo = val2_lo;
            transp[l + (DIM / 64)].hi = val2_hi;
        }
    }
    
    for (l = 0; l < DIM; l += 2) {
        val1_lo = (transp[l].lo & Cst1) | ((transp[l + 1].lo & Cst1) << 1);
        val1_hi = (transp[l].hi & Cst1) | ((transp[l + 1].hi & Cst1) << 1);
        val2_lo = ((transp[l].lo >> 1) & Cst1) | (transp[l + 1].lo & (Cst1 << 1));
        val2_hi = ((transp[l].hi >> 1) & Cst1) | (transp[l + 1].hi & (Cst1 << 1));
        transp[l].lo = val1_lo;
        transp[l].hi = val1_hi;
        transp[l + 1].lo = val2_lo;
        transp[l + 1].hi = val2_hi;
    }
}


void init_identity128(WORD128 mat[DIM]) {
    int l;
    for (l = 0; l < DIM; l++) {
        mat[l].lo = (l < 64) ? ((WORD)1 << l) : 0;
        mat[l].hi = (l >= 64) ? ((WORD)1 << (l - 64)) : 0;
    }
}

void init_all_ones128(WORD128 mat[DIM]) {
    int l;
    for (l = 0; l < DIM; l++) {
        mat[l].lo = ~((WORD)0);
        mat[l].hi = ~((WORD)0);
    }
}

void init_antidiagonal128(WORD128 mat[DIM]) {
    int l;
    for (l = 0; l < DIM; l++) {
        mat[l].lo = (l < 64) ? ((WORD)1 << (63 - l)) : 0;
        mat[l].hi = (l >= 64) ? ((WORD)1 << (127 - l)) : 0;
    }
}

void init_symmetric128(WORD128 mat[DIM]) {
    int l, c;
    for (l = 0; l < DIM; l++) {
        mat[l].lo = 0;
        mat[l].hi = 0;
        for (c = 0; c <= l; c++) {
             if (l != c) {
                flipbit128(mat, l, c);
                flipbit128(mat, c, l);
            }
        }
    }
}