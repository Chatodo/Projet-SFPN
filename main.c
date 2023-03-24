#ifdef TRANSPOSE1
	#include "matrice.h"
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
#elif defined(TRANSPOSE2)
	#include "matrice128.h"
	int main() {
		WORD128 mat1[DIM];
		matrice_1(mat1);
		printf("\nmatrice 1 :\n");
		print_mat128(mat1);
		return 0;
	}
#endif