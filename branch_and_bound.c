#include "branch_and_bound.h"
#include <stdio.h>
#include <stdlib.h>

// Cria uma solução inicial (gulosa) para a Mochila 0-1, 
// considerando os itens a partir do nível 'level' com capacidade 'w'
void initial_solution(int level, int w, int n, int *solution, int *weigh) {
    for (int i = level; i < n; i++) {
        solution[i] = 0;
        if (weigh[i] <= w) {
            w -= weigh[i];
            solution[i] = 1;
        }
    }
}

// Calcula o valor total da solução da mochila 0-1
int calc_value(int n, int *solution, int *value) {
    int total = 0;
    for (int i = 0; i < n; i++)
        total += solution[i] * value[i];
    return total;
}

// Copia uma solução do vetor 'src' para o vetor 'dest'
void copy_solution(int n, int *dest, int *src) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

// Função branch and bound com poda baseada em limite guloso
void branch_and_bound(int *current, int level, int *best_value, int *best_solution,
                      int *weigh, int *value, int n, int w) {
    // Se já foram considerados todos os itens, atualiza a melhor solução se for o caso
    if (level == n) {
        int curr_val = calc_value(n, current, value);
        if (curr_val > *best_value) {
            *best_value = curr_val;
            copy_solution(n, best_solution, current);
        }
        return;
    }
    
    // Calcula um limite superior para a ramificação atual usando solução gulosa
    int temp[n];
    copy_solution(n, temp, current);
    initial_solution(level, w, n, temp, weigh);
    int bound = calc_value(n, temp, value);
    
    // Se o limite não for promissor, poda a ramificação
    if (bound <= *best_value)
        return;
    
    // Ramificação sem incluir o item atual
    current[level] = 0;
    branch_and_bound(current, level + 1, best_value, best_solution, weigh, value, n, w);
    
    // Ramificação incluindo o item atual, se couber na capacidade restante
    if (weigh[level] <= w) {
        current[level] = 1;
        branch_and_bound(current, level + 1, best_value, best_solution, weigh, value, n, w - weigh[level]);
    }
}

// Função principal que lê os casos de teste e resolve o problema da mochila
void bb_knapsack(int w, int *result) {
    for (int a = 1; a <= ENTRIES; a++) {
        int n = 0;
        char fp[20];
        sprintf(fp, "Input/%02d.txt", a);
        // sprintf(fp, "Input/00.txt");
        
        FILE *file = fopen(fp, "r");
        if (!file) {
            perror("Erro ao abrir o arquivo");
            continue;
        }
        
        fscanf(file, "%d", &n);
        
        int *weigh = (int *)malloc(n * sizeof(int));
        int *value = (int *)malloc(n * sizeof(int));
        if (!weigh || !value) {
            perror("Erro ao alocar memória");
            fclose(file);
            return;
        }
        
        for (int i = 0; i < n; i++)
            fscanf(file, "%d %d", &weigh[i], &value[i]);
        fclose(file);
        
        // Aloca vetores para a solução corrente e a melhor solução encontrada
        int *current = (int *)calloc(n, sizeof(int));
        int *best_solution = (int *)calloc(n, sizeof(int));
        int best = 0;
        
        // Gera uma solução inicial (gulosa)
        initial_solution(0, w, n, current, weigh);
        best = calc_value(n, current, value);
        copy_solution(n, best_solution, current);
        
        branch_and_bound(current, 0, &best, best_solution, weigh, value, n, w);
        
        // Copia a melhor solução encontrada para o vetor 'result'
        copy_solution(n, result, best_solution);
        
        // printf("W = %d, N = %d; best_solution = %d\n", w, n, calc_value(n, result, value));
        // for(int i = 0; i < n; i++)
            // printf("%d ", result[i]);
        // printf("\n");

        free(weigh);
        free(value);
        free(current);
        free(best_solution);
    }
}
