#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

// Fonction de test pour la transposition
#ifdef TRANSPOSE1
#include "matrice.h"
    void test_transpose(WORD expected[DIM], WORD input[DIM]) {
        WORD result[DIM];
        init_zero(result);
        Transpose(result, input);
        bool passed = true;
        for (int i = 0; i < DIM; i++) {
            if (result[i] != expected[i]) {
                printf("--ICI %d--\n", i);
                printf("result[i] = %lu expected[i] = %lu", result[i], expected[i]);
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
        WORD mat1[DIM], mat2[DIM], mat3[DIM], mat4[DIM], mat5[DIM], mat6[DIM], mat7[DIM], mat8[DIM];
        input_mat(mat1);
        init_zero(mat2);
        Transpose(mat2, mat1);
        init_zero(mat3);
        printf("Test transpose: ");test_transpose(mat2, mat1); // Test 1
        printf("Test transpose * 2: ");test_transpose(mat1, mat2); // Test 2
        printf("Test Matrice uniquement 0: ");test_transpose(mat3, mat3); // Test 3
        init_identity(mat4);
    printf("4\n");
    test_transpose(mat4, mat4);

    // Test 5 : Matrice remplie de 1
    init_all_ones(mat5);
    printf("5\n");
    test_transpose(mat5, mat5);

    // Test 6 : Matrice anti-diagonale
    init_antidiagonal(mat6);
    printf("6\n");
    test_transpose(mat6, mat6);

    // Test 7 : Matrice symétrique
    init_symmetric(mat7); // On réutilise mat1
    printf("7\n");
    print_mat(mat7);
    Transpose(mat8, mat7);
    print_mat(mat7);
    test_transpose(mat8, mat7);
    #elif defined(TRANSPOSE2)
        // Partie 128 bits
        WORD128 mat1[DIM], mat2[DIM], mat3[DIM], mat4[DIM], mat5[DIM], mat6[DIM], mat7[DIM], mat8[DIM];
        input_mat128(mat1);
        init_zero128(mat2);
        Transpose128(mat2, mat1);
        init_zero128(mat3);
        printf("4 Tests : \n"); // Nombre de tests
        test_transpose128(mat2, mat1); // Test 1
        test_transpose128(mat1, mat2); // Test 2
        test_transpose128(mat3, mat3); // Test 3
        test_transpose128(mat4, mat4); // Test 4

        init_all_ones128(mat5);
    printf("5\n");
    test_transpose128(mat5, mat5);

    // Test 6 : Matrice anti-diagonale
    init_antidiagonal128(mat6);
    printf("6\n");
    test_transpose128(mat6, mat6);

    // Test 7 : Matrice symétrique
    init_symmetric128(mat7); // On réutilise mat1
    Transpose128(mat8, mat7);
    test_transpose128(mat8, mat7);
    #endif
    return 0;
}
