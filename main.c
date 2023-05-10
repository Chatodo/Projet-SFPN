//Fichier test pour les matrices
#include "matrices/matrice.h"
#include <papi.h>

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
		input_mat128(mat1);
		init_zero128(mat2);

		int retval;
		retval = PAPI_library_init(PAPI_VER_CURRENT);
		if (retval != PAPI_VER_CURRENT) {
			printf("Failed to initialize PAPI\n");
			exit(1);
		}
		int EventSet = PAPI_NULL;
		long_long values[2];

		retval = PAPI_create_eventset(&EventSet);
		if (retval != PAPI_OK) {
			printf("Failed to create PAPI event set\n");
			exit(1);
		}
		retval = PAPI_add_event(EventSet, PAPI_TOT_CYC);
		if (retval != PAPI_OK) {
			printf("Failed to add PAPI_TOT_CYC event\n");
			exit(1);
		}
		retval = PAPI_add_event(EventSet, PAPI_TOT_INS);
		if (retval != PAPI_OK) {
			printf("Failed to add PAPI_TOT_INS event\n");
			exit(1);
		}
		retval = PAPI_start(EventSet);
		if (retval != PAPI_OK) {
			printf("Failed to start PAPI counters\n");
			exit(1);
		}

		//printf("\nmatrice 1 :\n");
		//print_mat128(mat1);
		Transpose128(mat2, mat1);

		retval = PAPI_stop(EventSet, values);
		if (retval != PAPI_OK) {
			printf("Failed to stop PAPI counters\n");
			exit(1);
		}
		printf("Time: %lld cycles\n", values[0]);
		printf("Cycles: %lld cycles\n", values[1]);
		PAPI_cleanup_eventset(EventSet);
		PAPI_destroy_eventset(&EventSet);

		//printf("\n\n\nmatrice 2 :\n");
		//print_mat128(mat2);
		return 0;
	}
	#elif defined(AVX2)
	
#endif