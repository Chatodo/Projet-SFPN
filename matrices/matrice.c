#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "matrice.h"

#ifdef M64
#define bit(M,l,c) ((M[l]>>c)&1)
#define flipbit(M,l,c) M[l]^=((uint64_t)1<<c)


// // Façon plus lisible/maintenable mais moins optimisée car pas parallèle

// int getbit(WORD mat[DIM], int l, int c) {
// 	int index = l * DIM + c;
// 	int word_index = index / DIM;
// 	int bit_index = index % DIM;
// 	return (mat[word_index] >> bit_index) & 1;
// }

// void setbit(WORD mat[DIM], int l, int c, int value) {
// 	int index = l * DIM + c;
// 	int word_index = index / DIM;
// 	int bit_index = index % DIM;
// 	if (value) {
// 		mat[word_index] |= (WORD)1 << bit_index;
// 	} else {
// 		mat[word_index] &= ~((WORD)1 << bit_index);
// 	}
// }

// void Transpose(WORD transp[DIM], WORD mat[DIM]) {
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

void Transpose(WORD transp[DIM], WORD mat[DIM]) {
	int l,l0,l1;
	WORD val1,val2;
	for (l=0;l<DIM/2;l++) {
		transp[l]=(mat[l]&Cst32)|((mat[l+(DIM/2)]&Cst32)<<32);
		transp[l+(DIM/2)]=((mat[l]>>32)&Cst32)| (mat[l+(DIM/2)]&(Cst32<<32));
	}
	for(l0=0;l0<2;l0++)
		for (l1=0;l1<DIM/4;l1++) {
			l=l0*(DIM/2)+l1;
			val1=(transp[l]&Cst16)|((transp[l+(DIM/4)]&Cst16)<<16);
			val2=((transp[l]>>16)&Cst16)|(transp[l+(DIM/4)]&(Cst16<<16));
			transp[l]=val1; transp[l+(DIM/4)]=val2;
		}
	for(l0=0;l0<4;l0++)
		for (l1=0;l1<DIM/8;l1++) {
			l=l0*(DIM/4)+l1;
			val1=(transp[l]&Cst8)|((transp[l+(DIM/8)]&Cst8)<<8);
			val2=((transp[l]>>8)&Cst8)|(transp[l+(DIM/8)]&(Cst8<<8));
			transp[l]=val1; transp[l+(DIM/8)]=val2;
		}
	for(l0=0;l0<8;l0++)
		for (l1=0;l1<DIM/16;l1++) {
			l=l0*(DIM/8)+l1;
			val1=(transp[l]&Cst4)|((transp[l+(DIM/16)]&Cst4)<<4);
			val2=((transp[l]>>4)&Cst4)|(transp[l+(DIM/16)]&(Cst4<<4));
			transp[l]=val1; transp[l+(DIM/16)]=val2;
		}
	for(l0=0;l0<16;l0++)
		for (l1=0;l1<DIM/32;l1++) {
			l=l0*(DIM/16)+l1;
			val1=(transp[l]&Cst2)|((transp[l+(DIM/32)]&Cst2)<<2);
			val2=((transp[l]>>2)&Cst2)|(transp[l+(DIM/32)]&(Cst2<<2));
			transp[l]=val1; transp[l+(DIM/32)]=val2;
		}
	for(l0=0;l0<32;l0++)
		for (l1=0;l1<DIM/64;l1++) {
			l=l0*(DIM/32)+l1;
			val1=(transp[l]&Cst1)|((transp[l+(DIM/64)]&Cst1)<<1);
			val2=((transp[l]>>1)&Cst1)|(transp[l+(DIM/64)]&(Cst1<<1));
			transp[l]=val1; transp[l+(DIM/64)]=val2;
		}
	for (l=0;l<DIM;l+=2) {
		val1=(transp[l]&Cst1)|((transp[l+1]&Cst1)<<1);
		val2=((transp[l]>>1)&Cst1)|(transp[l+1]&(Cst1<<1));
		transp[l]=val1; transp[l+1]=val2;
	}
}

void input_mat(WORD mat[DIM]) {
	int l,c,val;
	for (l=0;l<DIM;l++) {
		mat[l]=0;
		for (c=0;c<DIM;c++) {
			if (c<DIM/2)
				val = 0;
			else
				val = 1;
			if (val) flipbit(mat,l,c);
		}
	}
}

void init_zero(WORD mat[DIM]) {
	int l;
	for (l=0;l<DIM;l++) {
		mat[l]=0;
	}
}

void print_mat(WORD mat[DIM]) {
	int l,c;
	for (l=0;l<DIM;l++) {
		for (c=0;c<DIM;c++) {
			printf("%lu ",bit(mat,l,c));
		}
		printf("\n");
	}
}

void init_identity(WORD mat[DIM]) {
	int l;
	for (l = 0; l < DIM; l++) {
		mat[l] = 0;
		flipbit(mat, l, l);
	}
}

void init_all_ones(WORD mat[DIM]) {
	int l;
	for (l = 0; l < DIM; l++) {
		mat[l] = ~(uint64_t)0;
	}
}

void init_antidiagonal(WORD mat[DIM]) {
	int l, c;
	for (l = 0; l < DIM; l++) {
		mat[l] = 0;
		c = DIM - (1 + l);
		flipbit(mat, l, c);
	}
}

void init_symmetric(WORD mat[DIM]) {
	int l, c;
	for (l = 0; l < DIM; l++) {
		mat[l] = 0;
		for (c = 0; c <= l; c++) {
			flipbit(mat, l, c);
		}
	}
}

#elif(M128)
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
void init_identity128(WORD128 mat[DIM]) {
    // Iterate through each row of the matrix
    for (int l = 0; l < DIM; l++) {
        mat[l].lo = 0;
        mat[l].hi = 0;
        flipbit128(mat, l, l);
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


// La même chose que la version 64bits

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


// void Transpose128(word128 transp[DIM], word128 mat[DIM]) {
// 	int l, l0, l1;
// 	word128 val1, val2;

// 	for (l = 0; l < DIM / 2; l++) {
// 		transp[l].lo = (mat[l].lo & Cst32) | ((mat[l + (DIM / 2)].lo & Cst32) << 32);
//         transp[l].hi = (mat[l].hi & Cst32) | ((mat[l + (DIM / 2)].hi & Cst32) << 32);
//         transp[l + (DIM / 2)].lo = ((mat[l].lo >> 32) & Cst32) | (mat[l + (DIM / 2)].lo & (Cst32 << 32));
//         transp[l + (DIM / 2)].hi = ((mat[l].hi >> 32) & Cst32) | (mat[l + (DIM / 2)].hi & (Cst32 << 32));
// 	}

// 	for (l0 = 0; l0 < 2; l0++) {
// 		for (l1 = 0; l1 < DIM / 4; l1++) {
// 			l = l0 * (DIM / 2) + l1;
// 			val1.lo = (transp[l].lo & Cst16) | ((transp[l + (DIM / 4)].lo & Cst16) << 16);
// 			val1.hi = (transp[l].hi & Cst16) | ((transp[l + (DIM / 4)].hi & Cst16) << 16);
// 			val2.lo = ((transp[l].lo >> 16) & Cst16) | (transp[l + (DIM / 4)].lo & (Cst16 << 16));
// 			val2.hi = ((transp[l].hi >> 16) & Cst16) | (transp[l + (DIM / 4)].hi & (Cst16 << 16));
// 			transp[l] = val1;
// 			transp[l + (DIM / 4)] = val2;
// 		}
// 	}

// 	for (l0 = 0; l0 < 4; l0++) {
// 		for (l1 = 0; l1 < DIM / 8; l1++) {
// 			l = l0 * (DIM / 4) + l1;
// 			val1.lo = (transp[l].lo & Cst8) | ((transp[l + (DIM / 8)].lo & Cst8) << 8);
// 			val1.hi = (transp[l].hi & Cst8) | ((transp[l + (DIM / 8)].hi & Cst8) << 8);
// 			val2.lo = ((transp[l].lo >>8) & Cst8) | (transp[l + (DIM / 8)].lo & (Cst8 << 8));
// 			val2.hi = ((transp[l].hi >> 8) & Cst8) | (transp[l + (DIM / 8)].hi & (Cst8 << 8));
// 			transp[l] = val1;
//             transp[l + (DIM / 8)] = val2;
// 		}
// 	}

// 	for (l0 = 0; l0 < 8; l0++) {
// 		for (l1 = 0; l1 < DIM / 16; l1++) {
// 			l = l0 * (DIM / 8) + l1;
// 			val1.lo = (transp[l].lo & Cst4) | ((transp[l + (DIM / 16)].lo & Cst4) << 4);
// 			val1.hi = (transp[l].hi & Cst4) | ((transp[l + (DIM / 16)].hi & Cst4) << 4);
// 			val2.lo = ((transp[l].lo >> 4) & Cst4) | (transp[l + (DIM / 16)].lo & (Cst4 << 4));
// 			val2.hi = ((transp[l].hi >> 4) & Cst4) | (transp[l + (DIM / 16)].hi & (Cst4 << 4));
// 			transp[l] = val1;
// 			transp[l + (DIM / 16)] = val2;
// 			}
// 	}

// 	for (l0 = 0; l0 < 16; l0++) {
// 		for (l1 = 0; l1 < DIM / 32; l1++) {
// 			l = l0 * (DIM / 16) + l1;
// 			val1.lo = (transp[l].lo & Cst2) | ((transp[l + (DIM / 32)].lo & Cst2) << 2);
// 			val1.hi = (transp[l].hi & Cst2) | ((transp[l + (DIM / 32)].hi & Cst2) << 2);
// 			val2.lo = ((transp[l].lo >> 2) & Cst2) | (transp[l + (DIM / 32)].lo & (Cst2 << 2));
// 			val2.hi = ((transp[l].hi >> 2) & Cst2) | (transp[l + (DIM / 32)].hi & (Cst2 << 2));
// 			transp[l] = val1;
// 			transp[l + (DIM / 32)] = val2;
// 		}
// 	}

// 	for (l0 = 0; l0 < 32; l0++) {
// 		for (l1 = 0; l1 < DIM / 64; l1++) {
// 			l = l0 * (DIM / 32) + l1;
// 			val1.lo = (transp[l].lo & Cst1) | ((transp[l + (DIM / 64)].lo & Cst1) << 1);
// 			val1.hi = (transp[l].hi & Cst1) | ((transp[l + (DIM / 64)].hi & Cst1) << 1);
// 			val2.lo = ((transp[l].lo >> 1) & Cst1) | (transp[l + (DIM / 64)].lo & (Cst1 << 1));
// 			val2.hi = ((transp[l].hi >> 1) & Cst1) | (transp[l + (DIM / 64)].hi & (Cst1 << 1));
// 			transp[l] = val1;
// 			transp[l + (DIM / 64)] = val2;
// 		}
// 	}
	
// 	for (l = 0; l < DIM; l += 2) {
// 		val1.lo = (transp[l].lo & Cst1) | ((transp[l + 1].lo & Cst1) << 1);
// 		val1.hi = (transp[l].hi & Cst1) | ((transp[l + 1].hi & Cst1) << 1);
// 		val2.lo = ((transp[l].lo >> 1) & Cst1) | (transp[l + 1].lo & (Cst1 << 1));
// 		val2.hi = ((transp[l].hi >> 1) & Cst1) | (transp[l + 1].hi & (Cst1 << 1));
// 		transp[l] = val1;
// 		transp[l + 1] = val2;
// 	}
// }

void Transpose(WORD transp[DIM64], WORD mat[DIM64]) {
	int l,l0,l1;
	WORD val1,val2;
	for (l=0;l<DIM64/2;l++) {
		transp[l]=(mat[l]&Cst32)|((mat[l+(DIM64/2)]&Cst32)<<32);
		transp[l+(DIM64/2)]=((mat[l]>>32)&Cst32)| (mat[l+(DIM64/2)]&(Cst32<<32));
	}
	for(l0=0;l0<2;l0++)
		for (l1=0;l1<DIM64/4;l1++) {
			l=l0*(DIM64/2)+l1;
			val1=(transp[l]&Cst16)|((transp[l+(DIM64/4)]&Cst16)<<16);
			val2=((transp[l]>>16)&Cst16)|(transp[l+(DIM64/4)]&(Cst16<<16));
			transp[l]=val1; transp[l+(DIM64/4)]=val2;
		}
	for(l0=0;l0<4;l0++)
		for (l1=0;l1<DIM64/8;l1++) {
			l=l0*(DIM64/4)+l1;
			val1=(transp[l]&Cst8)|((transp[l+(DIM64/8)]&Cst8)<<8);
			val2=((transp[l]>>8)&Cst8)|(transp[l+(DIM64/8)]&(Cst8<<8));
			transp[l]=val1; transp[l+(DIM64/8)]=val2;
		}
	for(l0=0;l0<8;l0++)
		for (l1=0;l1<DIM64/16;l1++) {
			l=l0*(DIM64/8)+l1;
			val1=(transp[l]&Cst4)|((transp[l+(DIM64/16)]&Cst4)<<4);
			val2=((transp[l]>>4)&Cst4)|(transp[l+(DIM64/16)]&(Cst4<<4));
			transp[l]=val1; transp[l+(DIM64/16)]=val2;
		}
	for(l0=0;l0<16;l0++)
		for (l1=0;l1<DIM64/32;l1++) {
			l=l0*(DIM64/16)+l1;
			val1=(transp[l]&Cst2)|((transp[l+(DIM64/32)]&Cst2)<<2);
			val2=((transp[l]>>2)&Cst2)|(transp[l+(DIM64/32)]&(Cst2<<2));
			transp[l]=val1; transp[l+(DIM64/32)]=val2;
		}
	for(l0=0;l0<32;l0++)
		for (l1=0;l1<DIM64/64;l1++) {
			l=l0*(DIM64/32)+l1;
			val1=(transp[l]&Cst1)|((transp[l+(DIM64/64)]&Cst1)<<1);
			val2=((transp[l]>>1)&Cst1)|(transp[l+(DIM64/64)]&(Cst1<<1));
			transp[l]=val1; transp[l+(DIM64/64)]=val2;
		}
	for (l=0;l<DIM64;l+=2) {
		val1=(transp[l]&Cst1)|((transp[l+1]&Cst1)<<1);
		val2=((transp[l]>>1)&Cst1)|(transp[l+1]&(Cst1<<1));
		transp[l]=val1; transp[l+1]=val2;
	}
}

void Transpose128(WORD128 transp[DIM], WORD128 mat[DIM]) {
    WORD temp64[DIM64];
    int i;

    for (i = 0; i < DIM64; i++) {
        temp64[i] = mat[i].lo;
    }
    Transpose(temp64, temp64);

    for (i = 0; i < DIM64; i++) {
        transp[i].lo = temp64[i];
    }

    for (i = 0; i < DIM64; i++) {
        temp64[i] = mat[i + DIM64].lo;
    }
    Transpose(temp64, temp64);

    for (i = 0; i < DIM64; i++) {
        transp[i].hi = temp64[i];
    }

    for (i = 0; i < DIM64; i++) {
        temp64[i] = mat[i].hi;
    }
    Transpose(temp64, temp64);

    for (i = 0; i < DIM64; i++) {
        transp[i + DIM64].lo = temp64[i];
    }

    for (i = 0; i < DIM64; i++) {
        temp64[i] = mat[i + DIM64].hi;
    }
    Transpose(temp64, temp64);

    for (i = 0; i < DIM64; i++) {
        transp[i + DIM64].hi = temp64[i];
    }
}
#endif