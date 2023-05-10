#ifndef MATRICE_H
#define MATRICE_H
//------------INCLUDES----------------
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#ifdef M64
//-------------DEFINITON--------------
//Dimension 64 bits
#define DIM 64
#define Cst1 0x5555555555555555
#define Cst2 0x3333333333333333
#define Cst4 0x0f0f0f0f0f0f0f0f
#define Cst8 0x00ff00ff00ff00ff
#define Cst16 0x0000ffff0000ffff
#define Cst32 0x00000000ffffffffULL
#define WORD uint64_t
//-------------PROTOTYPES-------------
// Fonction pour initialiser une matrice avec des valeurs prédéfinies (ici : 0 et que des 1 à partir de la moitié de la matrice)
void input_mat(WORD mat[DIM]);

// Fonction pour initialiser une matrice avec des valeurs nulles
void init_zero(WORD mat[DIM]);

// Fonction pour initialiser une matrice identité
void init_identity(WORD mat[DIM]);

// Fonction pour initialiser une matrice avec des valeurs 1 partout
void init_all_ones(WORD mat[DIM]);

// Tous les éléments de l'antidiagonale = 1, sinon = 0
void init_antidiagonal(WORD mat[DIM]);
// Tous les éléments au-dessus et sur la diagonale = 1, sinon = 0
void init_symmetric(WORD mat[DIM]);

// Fonction pour afficher une matrice
void print_mat(WORD mat[DIM]);

// La fonction Transpose transpose la matrice "mat" et stocke le résultat dans la matrice "transp"
// Principe : divise la matrice en groupes de lignes et échange les parties gauche et droite des mots de chaque ligne en utilisant des opérations bit à bit
// Méthode parallèle
void Transpose(WORD transp[DIM], WORD mat[DIM]);


#elif(M128)
//-------------DEFINITON--------------
//Dimension 128 bits
#define DIM64 64
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

void init_identity128(WORD128 mat[DIM]);
void init_all_ones128(WORD128 mat[DIM]);
void init_antidiagonal128(WORD128 mat[DIM]);
void init_symmetric128(WORD128 mat[DIM]);


// La fonction Transpose transpose la matrice "mat" et stocke le résultat dans la matrice "transp". 
// Principe : divise la matrice en groupes de lignes et en échange les parties gauche et droite des mots de chaque ligne. (en bit à bit)
// Méthode parallèle
// void Transpose128(word128 transp[DIM], word128 mat[DIM]);
void Transpose(WORD transp[DIM64], WORD mat[DIM64]);
void Transpose128(WORD128 transp[DIM], WORD128 mat[DIM]);
void Transpose128_Naif(WORD128 transp[DIM], WORD128 mat[DIM]);

#elif(AVX2)
#include <immintrin.h>
//-------------DEFINITON--------------
//Dimension 256 bits
#define DIM64 64
#define DIM128 128
#define DIM 256
#define Cst1 0x5555555555555555
#define Cst2 0x3333333333333333
#define Cst4 0x0f0f0f0f0f0f0f0f
#define Cst8 0x00ff00ff00ff00ff
#define Cst16 0x0000ffff0000ffff
#define Cst32 0x00000000ffffffffULL
// Fonction pour initialiser une matrice avec des valeurs prédéfinies
void input_mat_AVX2(__m256i mat[DIM]);

#endif
#endif