#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// UNIX SPECIFIC TIMING
#include <time.h>

#include "src/list_generics.h"
#include "src/list_interface.h"
#include "src/sorters.h"

int main (int argc, char **argv){
    // Default Test Size
    srand(time(NULL));
    int n = 5000;

    const char * stuff[] = {
        "BubbleSort", "InsertionSort"
    };

    void (*arr[])(list*, int) = {
        &bubblesort, &insertionsort 
    };
    int sort_count = 2;

    // Default Iteration Count
    int iter = 3;

    if (argc > 1){
        n = atoi(*(argv + 1));
    }

    if (argc > 2){
        iter = atoi(*(argv + 2));
    }

    printf("Profile using: sample size count n=%d; iteration count iter=%d\n", n, iter);
    printf("Generating samples..."); 

    list*** l_test_suite = malloc(sizeof(list**) * sort_count);
    
    // Generate sort_count Test Suites consisting of iter Test Collections consisting of lists with n sample size
    for (int suite = 0; suite < sort_count; suite++){
        l_test_suite[suite] = malloc(sizeof(list*) * iter);

        for (int i = 0; i < iter; i++){
            l_test_suite[suite][i] = l_new();

            for(int arr_idx = 0; arr_idx < n; arr_idx++){
                int *item = malloc(sizeof(item));
                *item = rand();
                l_insert(l_test_suite[suite][i], item, arr_idx);
            }
        }
    }
    printf("done\n");

    for (int i = 0; i < sort_count; i++){
        for (int run = 0; run < iter; run++){
            struct timespec start, stop;
            printf("%s\t(run:%d)\t", stuff[i], run+1);
            
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
            arr[i](l_test_suite[i][run], n-1);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
            double secs = stop.tv_nsec/10e6
                - start.tv_nsec/10e6;
            printf("took t=%f\n", secs);
        } 
    }
}
