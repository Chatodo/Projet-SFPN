#ifndef MATRICE128_H
#define MATRICE128_H
//------------INCLUDES----------------
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

//-------------DEFINITON--------------
//Dimension 128 bits
#define DIM 128
#define Cst1 0x5555555555555555
#define Cst2 0x3333333333333333
#define Cst4 0x0f0f0f0f0f0f0f0f
#define Cst8 0x00ff00ff00ff00ff
#define Cst16 0x0000ffff0000ffff
#define Cst32 0x00000000ffffffffULL
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

// La fonction Transpose transpose la matrice "mat" et stocke le résultat dans la matrice "transp". 
// Principe : divise la matrice en groupes de lignes et en échange les parties gauche et droite des mots de chaque ligne. (en bit à bit)
//void Transpose128(WORD128 transp[DIM], WORD128 mat[DIM]);
#endif