#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cblas.h>

double* alloc_matrix(int n) {
    double *m = malloc(sizeof(double) * (size_t)n * n);
    for (long i = 0; i < (long)n*n; i++) m[i] = (double)rand() / RAND_MAX;
    return m;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <matrix_size>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);

    double *A = alloc_matrix(n);
    double *B = alloc_matrix(n);
    double *C = calloc((size_t)n * n, sizeof(double));

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                n, n, n, 1.0, A, n, B, n, 0.0, C, n);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time_sec = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    double flops = 2.0 * n * n * n;
    double gflops = (flops / time_sec) / 1e9;

    printf("%d,%.6f,%.4f\n", n, time_sec, gflops);

    free(A); free(B); free(C);
    return 0;
}
