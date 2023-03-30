#include <stdio.h>
#include <stdlib.h>
#include <papi.h>
#include "../matrices/matrice.h"
//ifdef M64
void measure_transpose() {
    int retval, EventSet = PAPI_NULL;
    long long values[1];

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

    retval = PAPI_start(EventSet);
    if (retval != PAPI_OK) {
        fprintf(stderr, "Error: PAPI start_counters failed.\n");
        exit(1);
    }

    // Transpose
    Transpose128(transp, mat);

    // Stop the COUNT
    retval = PAPI_stop(EventSet, values);
    if (retval != PAPI_OK) {
        fprintf(stderr, "Error: PAPI stop_counters failed.\n");
        exit(1);
    }

    printf("Number of cycles: %lld\n", values[0]);

    // Free the EventSet and clean up
    retval = PAPI_cleanup_eventset(EventSet);
    retval = PAPI_destroy_eventset(&EventSet);
    PAPI_shutdown();
}

int main() {
    measure_transpose();
    return 0;
}
