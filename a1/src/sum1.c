/*

COL380. assignment 1.

Problem:

Compute the sum of the First N natural numbers.

The sequential version is provided below.

1. Develop two parallel versions of the given program using OpenMP `parallel
for' with maximum 8 threads.

Compilation command: gcc -O0 ...

2. The speedup and efficiency of both parallel versions for 2, 4, 8 threads for
N=10^3, N=10^6, and N=10^9 numbers.

3. Does the speedup follow Amdahl's law?

Hint: Use a time function in the program (e.g. omp_get_wtime) to measure the
time.

*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    long long sum = 0;
    int *a;

    int N = 1000;
    int NUM_THREADS = 8;

    if (argc == 2) {
        N = atoi(argv[1]);
    } else if (argc >= 3) {
        N = atoi(argv[1]);
        NUM_THREADS = atoi(argv[2]);
    }

    printf("--------------------------------\n");
    printf("N \t\t= %d\n", N);
    printf("NUM_THREADS \t= %d\n", NUM_THREADS);

    a = (int *)malloc(sizeof(int) * N);

    a[0] = 1;
    for (int i = 1; i < N; i++) a[i] = a[i - 1] + 1;

    double start_time = omp_get_wtime();
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
    double end_time = omp_get_wtime();
    printf("time elapsed\t= %lf\n", end_time - start_time);

    printf("sum\t\t= %lld\n", sum);

    free(a);

    return 0;
}
