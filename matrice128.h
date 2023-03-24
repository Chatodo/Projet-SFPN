#ifndef MATRICE128_H
#define MATRICE128_H
//------------INCLUDES----------------
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

//-------------DEFINITON--------------
//Dimension 128 bits
#define DIM 128
#define Cst64lo 0xFFFFFFFFFFFFFFFF
#define Cst64hi 0xFFFFFFFFFFFFFFFF
#define Cst32lo 0x0000FFFF0000FFFF
#define Cst32hi 0x0000FFFF0000FFFF
#define Cst16lo 0x00FF00FF00FF00FF
#define Cst16hi 0x00FF00FF00FF00FF
#define Cst8lo 0x0F0F0F0F0F0F0F0F
#define Cst8hi 0x0F0F0F0F0F0F0F0F
#define Cst4lo 0x3333333333333333
#define Cst4hi 0x3333333333333333
#define Cst2lo 0x5555555555555555
#define Cst2hi 0x5555555555555555
#define Cst1lo 0xAAAAAAAAAAAAAAAA
#define Cst1hi 0xAAAAAAAAAAAAAAAA
#define WORD uint64_t
// 128 bits --> 2 mots de 64 bits
typedef struct {
    uint64_t lo;
    uint64_t hi;
}word128;
#define WORD128 word128
//-------------PROTOTYPES-------------
// Fonction pour initialiser une matrice avec des valeurs prédéfinies
void input_mat128(WORD128 mat[DIM]);

// Fonction pour initialiser une matrice avec des valeurs nulles
void init_zero128(WORD128 mat[DIM]);

// Fonction pour afficher une matrice
void print_mat128(WORD128 mat[DIM]);

void matrice_1(WORD128 mat[DIM]);


// La fonction Transpose transpose la matrice "mat" et stocke le résultat dans la matrice "transp". 
// Principe : divise la matrice en groupes de lignes et en échange les parties gauche et droite des mots de chaque ligne. (en bit à bit)
void Transpose128(WORD128 transp[DIM], WORD128 mat[DIM]);
#endif