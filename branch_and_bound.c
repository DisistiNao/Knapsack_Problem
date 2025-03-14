#include "branch_and_bound.h"
#include <stdio.h>
#include <stdlib.h>

void initial_solution(int level, int k, int n, int *result, int *weigh) {
    for(int i = 0; i < n; i++) {
        if(i < level)
            k -= weigh[i];
        else if(weigh[i] <= k) {
            k -= weigh[i];
            result[i] = 1;
        }
    }
    return;
}

int calc_value(int n, int weigh, int value) {
    int value = 0;

    for(int i = 0; i < n; i++)
        value += weigh[i] * value[i];

    return value;
}

void bb_knapsack(int w, int *result) {
    for(int a = 1; a <= 20; a++) {
        int n = 0;
        char fp[20];  
        sprintf(fp, "Input/%02d.txt", a);
        
        FILE* file = fopen (fp, "r");
        
        if (!file) { 
            perror("Erro ao abrir o arquivo");
            continue;
        }

        fscanf (file, "%d", &n);
        
        int *weigh = (int *)malloc(n * sizeof(int));
        int *value = (int *)malloc(n * sizeof(int));

        if (!weigh || !value) {
            perror("Erro ao alocar memória");
            fclose(file);
            return;
        }

        for(int i = 1; i <= n; i++) 
            fscanf(file, "%d %d", &weigh[i-1], &value[i-1]);

        fclose (file);
        
        int *initial = (int *)calloc(n, sizeof(int));
        initial_solution(0, k, n, result, weigh);
        
        int better = calc_value(n, weigh, value);

        branch_and_bound(n, k, weigh, value, better, result, 1);
    }
    return;
}

void branch_and_bound(int n, int k, int *weigh, int *value, int better, int *result, int level) {
    initial_solution(1, k, n, result, weigh);
    int local = calc_value(n, weigh, value);
    
    if(local > better)
        // dfadsfads
}
