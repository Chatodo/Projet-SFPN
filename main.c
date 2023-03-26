//Fichier test pour les matrices
#include "matrice.h"
#ifdef M64
	int main() {
		WORD mat1[DIM]; WORD mat2[DIM]; WORD mat3[DIM]; //int count;
		input_mat(mat1);
		init_zero(mat2);
		init_zero(mat3);
		printf("\nmatrice 1 :\n");
		print_mat(mat1);
		Transpose(mat2, mat1);
		printf("\n\n\nmatrice 2 :\n");
		print_mat(mat2);
		printf("\n\n\nmatrice res :\n");
		Transpose(mat3, mat2);
		print_mat(mat3);
		return 0;
	}
#elif defined(M128)
	int main() {
		WORD128 mat1[DIM], mat2[DIM];
		init_identity128(mat1);
		//print_mat128(mat1);
		Transpose128(mat2, mat1);
		print_mat128(mat2);
		return 0;
	}
#endif