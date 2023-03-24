#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

// Fonction de test pour la transposition
#ifdef TRANSPOSE1
#include "matrice.h"
    void test_transpose(WORD expected[DIM], WORD input[DIM]) {
        WORD result[DIM];
        Transpose(result, input);
        bool passed = true;
        for (int i = 0; i < DIM; i++) {
            if (result[i] != expected[i]) {
                passed = false;
                break;
            }
        }
        if (passed) {
            printf("ok\n");
        } else {
            printf("not ok\n");
        }
    }

#elif defined(TRANSPOSE2)
#include "matrice128.h"
    void test_transpose128(WORD128 expected[DIM], WORD128 input[DIM]) {
        WORD128 result[DIM];
        Transpose128(result, input);
        bool passed = true;
        for (int i = 0; i < DIM; i++) {
            if (result[i].lo != expected[i].lo || result[i].hi != expected[i].hi) {
                passed = false;
                break;
            }
        }
        if (passed) {
            printf("ok\n");
        } else {
            printf("not ok\n");
        }
    }
#endif

int main() {
    #ifdef TRANSPOSE1
        WORD mat1[DIM], mat2[DIM], mat3[DIM];
        input_mat(mat1);
        init_zero(mat2);
        Transpose(mat2, mat1);
        init_zero(mat3);
        printf("1..3\n"); // Nombre de tests
        test_transpose(mat2, mat1); // Test 1
        test_transpose(mat1, mat2); // Test 2
        test_transpose(mat3, mat3); // Test 3
    #elif defined(TRANSPOSE2)
        // Partie 128 bits
        WORD128 mat1[DIM], mat2[DIM], mat3[DIM], mat4[DIM];
        input_mat128(mat1);
        init_zero128(mat2);
        Transpose128(mat2, mat1);
        init_zero128(mat3);
        printf("1..3\n"); // Nombre de tests
        test_transpose128(mat2, mat1); // Test 1
        test_transpose128(mat1, mat2); // Test 2
        test_transpose128(mat3, mat3); // Test 3
        matrice_1(mat4);
        test_transpose128(mat4, mat4); // Test 4
    #endif
    return 0;
}
