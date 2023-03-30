#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include "../matrices/matrice.h"

#ifdef M64
	bool test_transpose(WORD expected[DIM], WORD input[DIM]) {
		WORD result[DIM];
		init_zero(result);
		Transpose(result, input);
		bool test = true;
		for (int i = 0; i < DIM; i++) {
			if (result[i] != expected[i]) {
				printf("\nErreur it : %d\n", i);
				printf("result[i] = %lu, expected[i] = %lu\n", result[i], expected[i]);
				test = false;
				break;
			}
		}

		if (test) {
			printf("ok\n");
		} 
		else {
			printf("not ok\n");
		}
		return test;
	}

#elif defined(M128)
	bool test_transpose128(WORD128 expected[DIM], WORD128 input[DIM]) {
		WORD128 result[DIM];
		Transpose128(result, input);
		bool test = true;
		for (int i = 0; i < DIM; i++) {
			if (result[i].lo != expected[i].lo || result[i].hi != expected[i].hi) {
				printf("\n---Erreur à la position (%d,%d):\n", i % 128, i / 128);
            	printf("Valeur attendue: lo=%lu, hi=%lu\n", expected[i].lo, expected[i].hi);
            	printf("Valeur réelle:   lo=%lu, hi=%lu\n", result[i].lo, result[i].hi);
				test = false;
				break;
			}
		}
		if (test) {
			printf("ok\n");
		} 
		else {
			printf("not ok\n");
		}
		return test;
	}
#endif

int main() {
	#ifdef M64
		WORD mat1[DIM], mat2[DIM], mat3[DIM], mat4[DIM], mat5[DIM], mat6[DIM], mat7[DIM], mat8[DIM];
		bool success = true;

		//Init matrice tests, nb tests = 7
		input_mat(mat1);
		init_zero(mat2);
		init_zero(mat3);
		init_identity(mat4);
		init_all_ones(mat5);
		init_antidiagonal(mat6);
		init_symmetric(mat7);
		//pour la symétrie
		Transpose(mat8,mat7); 

		Transpose(mat2, mat1);
		printf("Test transpose: "); success &= test_transpose(mat2, mat1); 
		printf("Test transpose * 2: "); success &= test_transpose(mat1, mat2);
		printf("Test Matrice uniquement 0: "); success &= test_transpose(mat3, mat3);
		printf("Test matrice identité: "); success &= test_transpose(mat4, mat4);
		printf("Test matrice uniquement 1: "); success &= test_transpose(mat5, mat5);
		printf("Test matrice anti-diagonale: "); success &= test_transpose(mat6, mat6);
		printf("Test matrice symétrique: "); success &= test_transpose(mat8, mat7);
		return 0;
//---------------------------------------------------------------------------------------------------
	#elif defined(M128)
		// Partie 128 bits
		WORD128 mat1[DIM], mat2[DIM], mat3[DIM], mat4[DIM], mat5[DIM], mat6[DIM], mat7[DIM], mat8[DIM];
		bool success = true;
	
		//Init matrice tests, nb tests = 7
		input_mat128(mat1);
		init_zero128(mat2);
		init_zero128(mat3);
		init_identity128(mat4);
		init_all_ones128(mat5);
		init_antidiagonal128(mat6);
		init_symmetric128(mat7);
		//pour la symétrie
		Transpose128(mat8,mat7); 

		Transpose128(mat2, mat1);
		printf("Test transpose: "); success &= test_transpose128(mat2, mat1); 
		printf("Test transpose * 2: "); success &= test_transpose128(mat1, mat2);
		printf("Test Matrice uniquement 0: "); success &= test_transpose128(mat3, mat3);
		printf("Test matrice identité: "); success &= test_transpose128(mat4, mat4);
		printf("Test matrice uniquement 1: "); success &= test_transpose128(mat5, mat5);
		printf("Test matrice anti-diagonale: "); success &= test_transpose128(mat6, mat6);
		printf("Test matrice symétrique: "); success &= test_transpose128(mat8, mat7);
		return 0;
	#endif
}
