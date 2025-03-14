#include "branch_and_bound.h"
#include <stdio.h>
#include <stdlib.h>

// Cria uma solução inicial para o problema da Mochila 0-1 sem repetição,
// onde level é a camada de profundidade na árvore
// e w é a capacidade máxima da mochila
void initial_solution(int level, int w, int n, int *result, int *weigh) {
    for(int i = 0; i < n; i++) {
        if(i < level)
            w -= weigh[i];
        else if(weigh[i] <= w) {
            w -= weigh[i];
            result[i] = 1;
        }
    }
    return;
}

int calc_value(int n, int result, int value) {
    int value = 0;

    for(int i = 0; i < n; i++)
        value += result[i] * value[i];

    return value;
}

void bb_knapsack(int w, int *result) {
    for(int a = 1; a <= ENTRIES; a++) {
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
        
        initial_solution(0, w, n, result, weigh);
    
        int better = calc_value(n, result, value);

        branch_and_bound(n, w, weigh, value, better, result, 1);
    }
    return;
}

void branch_and_bound(int n, int w, int *weigh, int *value, int better, int *result, int level) {
    int *initial = (int *)calloc(n, sizeof(int));
    initial_solution(1, w, n, initial, weigh);
    
    int local = calc_value(n, initial, value);
    
    if(local > better)
        
    else
        return;
}
