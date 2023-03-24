#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "matrice.h"
#define bit(M,l,c) ((M[l]>>c)&1)
#define flipbit(M,l,c) M[l]^=((uint64_t)1<<c)

void Transpose(WORD transp[DIM], WORD mat[DIM]) {
    int l,l0,l1;
    WORD val1,val2;
    for (l=0;l<DIM/2;l++) {
        transp[l]=(mat[l]&Cst32)|((mat[l+(DIM/2)]&Cst32)<<32);
        transp[l+(DIM/2)]=((mat[l]>>32)&Cst32)|
        (mat[l+(DIM/2)]&(Cst32<<32));
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
