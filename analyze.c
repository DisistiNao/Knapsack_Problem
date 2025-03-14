#include <stdio.h>
#include <time.h>
#include <math.h>

#include "input_generator.h"
#include "dynamic_prog.h"
#include "backtrack.h"

// gcc -Wall -o prog analyze.c dynamic_prog.c input_generator.c -lm

int main() {
    int result[20];
    int w = 100, n = 100;

    clock_t start, end;
    double dif;

    for(int i = 0; i < 10; i++) {
        n = 100 * pow(2, i);
        
        start = clock();
        
        generator(n);
        dynamic_knapsack(w, result);
        //backtrack_knapsack(w, result);

        end = clock();
        dif = (double)(end - start) / CLOCKS_PER_SEC;
        printf ("%.6lf seconds to execute when W = %d and N = %d.\n", dif, w, n);
    }

    printf("\n");

    n = 400;

    for(int i = 0; i < 10; i++) {
        w = 100 * pow(2, i);
        
        start = clock();
        
        generator(n);
        dynamic_knapsack(w, result);
        
        end = clock();
        dif = (double)(end - start) / CLOCKS_PER_SEC;
        printf ("%.6lf seconds to execute when W = %d and N = %d.\n", dif, w, n);
    }

    return 0;
}
