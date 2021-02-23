/*

COL380. assignment 1.

Problem:

Compute the sum of the First N natural numbers.

The sequential version is provided below.

1. Develop two parallel versions of the given program using OpenMP `parallel
for' with maximum 8 threads.

Compilation command: gcc -O0 ...

2. The speedup and efficiency of both parallel versions for 2, 4, 8 threads for
N=10^3, N=10^5, and N=10^7 numbers.

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
    long long *b;

    int N = 1000;
    int NUM_THREADS = 8;

    if (argc == 2) {
        N = atoi(argv[1]);
    } else if (argc >= 3) {
        N = atoi(argv[1]);
        NUM_THREADS = atoi(argv[2]);
    }

    printf("N \t\t= %d\n", N);
    printf("NUM_THREADS \t= %d\n", NUM_THREADS);

    a = (int *)malloc(sizeof(int) * N);
    b = (long long *)malloc(sizeof(long long) * NUM_THREADS);

    a[0] = 1;
    for (int i = 1; i < N; i++) a[i] = a[i - 1] + 1;

    double start_time = omp_get_wtime();
    int depth = -1;
    do {
        ++depth;
#pragma omp parallel num_threads(NUM_THREADS / (1 << depth))
        {
            if (depth == 0) {
                {
                    long long s = 0;
                    int i = 0;
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
    double end_time = omp_get_wtime();
    printf("time taken\t= %lf\n", end_time - start_time);
    printf("sum\t\t= %lld\n", sum);

    free(a);
    free(b);

    return 0;
}
