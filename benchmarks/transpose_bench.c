#include <stdio.h>
#include <stdlib.h>
#include <papi.h>
#include <math.h>
#include "../matrices/matrice.h"
#define NB_TESTS 10
//ifdef M64
void measure_transpose(long long *values, void (*transpose_fonction)(word128[DIM], word128[DIM])) {
    int retval, EventSet = PAPI_NULL;

    //Les fonctions pour matrices 
    word128 mat[DIM], transp[DIM];
    input_mat128(mat);
    init_zero128(transp);


    // Tout les trucs pour initialiser PAPI et les compteurs
    retval = PAPI_library_init(PAPI_VER_CURRENT);
    if (retval != PAPI_VER_CURRENT) {
        fprintf(stderr, "Error: PAPI library initialization failed.\n");
        exit(1);
    }

    retval = PAPI_create_eventset(&EventSet);
    if (retval != PAPI_OK) {
        fprintf(stderr, "Error: PAPI create_eventset failed.\n");
        exit(1);
    }

    retval = PAPI_add_event(EventSet, PAPI_TOT_CYC);
    if (retval != PAPI_OK) {
        fprintf(stderr, "Error: PAPI add_event failed.\n");
        exit(1);
    }

    for(int i = 0; i < NB_TESTS; i++){
        retval = PAPI_start(EventSet);
        if (retval != PAPI_OK) {
            fprintf(stderr, "Error: PAPI start_counters failed.\n");
            exit(1);
        }

        // Transpose
        transpose_fonction(transp, mat);

        // Stop the COUNT
        retval = PAPI_stop(EventSet, &values[i]);
        if (retval != PAPI_OK) {
            fprintf(stderr, "Error: PAPI stop_counters failed.\n");
            exit(1);
        }
    }
    // Free the EventSet and clean up
    retval = PAPI_cleanup_eventset(EventSet);
    retval = PAPI_destroy_eventset(&EventSet);
    PAPI_shutdown();
}

void afficher_result(long long *values) {
    double moyenne = 0;
    for(int i = 0; i < NB_TESTS; i++){
        moyenne += values[i];
    }
    moyenne /= NB_TESTS;

    double variance = 0;
    for(int i = 0; i < NB_TESTS; i++){
        variance += pow(values[i] - moyenne, 2);
    }
    variance /= NB_TESTS;

    printf("Nombre de cycles (en moyenne): %lf\n", moyenne);
    printf("Variance: %lf\n", variance);
}

int main() {
    long long values[NB_TESTS];
    printf("Transpose naif:\n");
    measure_transpose(values, Transpose128_Naif);
    afficher_result(values);
    printf("--------------------------------:\n");
    printf("Transpose Optimise:\n");
    measure_transpose(values, Transpose128);
    afficher_result(values);
    return 0;
}
