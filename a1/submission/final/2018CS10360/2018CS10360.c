#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main(int argc, char *argv[]) {
    int strategy, N, NUM_THREADS;
    if (argc != 4) {
        fprintf(stderr, "usage format: %s <strategy> <N> <number of threads>",
                argv[0]);
        return 0;
    }

    strategy = atoi(argv[1]);
    N = atoi(argv[2]);
    NUM_THREADS = atoi(argv[3]);

    double global_start_time = omp_get_wtime();
    long long sum = 0;
    int *a;

    a = (int *)malloc(sizeof(int) * N);
    a[0] = 1;
    for (int i = 1; i < N; i++) a[i] = a[i - 1] + 1;

    double start_time = omp_get_wtime();
    if (strategy == 0) {
#pragma omp parallel num_threads(NUM_THREADS)
        {
            long long t = 0;
#pragma omp for
            for (int i = 0; i < N; i++) {
                t += a[i];
            }
#pragma omp critical
            sum += t;
        }
    } else {
        long long *b = (long long *)malloc(sizeof(long long) * NUM_THREADS);
        int depth = -1;
        do {
            ++depth;
#pragma omp parallel num_threads(MAX(1, NUM_THREADS >> depth))
            {
                if (depth == 0) {
                    {
                        long long s = 0;
                        int i = 0;
                        int tr = omp_get_thread_num();
#pragma omp for
                        for (i = 0; i < N; ++i) s += a[i];
                        b[omp_get_thread_num()] = s;
                    }
                } else {
                    {
                        int t = omp_get_thread_num() << depth;
                        if (t < NUM_THREADS &&
                            (t + (1 << (depth - 1)) < NUM_THREADS)) {
                            b[t] += b[t + (1 << (depth - 1))];
                        }
                    }
                }
            }
        } while ((1 << depth) < NUM_THREADS);
        sum = b[0];
        free(b);
    }

    free(a);
    double end_time = omp_get_wtime();

    /* statistics */
    // printf("--------------------------------\n");
    // printf("strategy\t= %d\n", strategy);
    // printf("N\t\t= %d\n", N);
    // printf("number of threads\t= %d\n", NUM_THREADS);
    // printf("parallel time\t= %lf\n", end_time - start_time);
    // printf("total time\t= %lf\n", end_time - global_start_time);
    // printf("sum\t\t= %lld\n", sum);
    printf("%lld\n", sum);

    return 0;
}
