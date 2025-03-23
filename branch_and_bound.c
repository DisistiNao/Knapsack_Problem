#include "branch_and_bound.h"
#include <stdio.h>
#include <stdlib.h>

// Cria uma solução inicial (gulosa) para a mochila 0-1, 
// considerando os itens a partir do nível 'level' com capacidade 'w'
void initial_solution(int level, int w, int n, int *solution, int *weight) {
    for(int i = level; i < n; i++) {
        solution[i] = 0;
        // Se o item cabe na mochila, adiciona
        if(weight[i] <= w) {
            w -= weight[i]; // diminui a capacidade da mochila
            solution[i] = 1;
        }
    }
}

// Calcula um limite superior para a poda
// int calc_bound(int level, int w, int n, int *weight, int *value) {
//     int bound = 0;

//     for(int i = level; i < n; i++) {
//         // Se o item cabe na mochila, adiciona
//         if(weight[i] <= w) {
//             bound += value[i];
//             w -= weight[i]; // diminui a capacidade da mochila
//         }
//         else {
//             break; // para não adicionar itens fracionados
//         }
//     }
//     return bound;
// }

// Calcula o valor total da solução da mochila 0-1
int calc_value(int n, int *solution, int *value) {
    int total = 0;
    for(int i = 0; i < n; i++)
        total += solution[i] * value[i];
    return total;
}

// Copia uma solução do vetor origem para o vetor destino
void copy_solution(int n, int *dest, int *src) {
    for(int i = 0; i < n; i++)
        dest[i] = src[i];
}

// Função branch and bound com poda baseada em limite guloso
void branch_and_bound(int *current, int level, int *best_value, int *best_solution,
                      int *weight, int *value, int n, int w) {
    
    // Se já foram considerados todos os itens, atualiza a melhor solução, se for o caso
    if(level == n) {
        int curr_val = calc_value(n, current, value);
        if(curr_val > *best_value) {
            *best_value = curr_val;
            copy_solution(n, best_solution, current);
        }
        return;
    }
    
    // Calcula um limite superior para a ramificação atual usando solução gulosa
    int temp[n];
    copy_solution(n, temp, current);
    initial_solution(level, w, n, temp, weight);
    int bound = calc_value(n, temp, value);

    // Calcula um limite superior
    // int bound = calc_value(level, current, value) + calc_bound(level, w, n, weight, value);
    
    // Se o limite não for promissor, poda a ramificação
    if(bound <= *best_value)
        return;
    
    // Ramificação incluindo o item atual, se couber na capacidade restante
    if(weight[level] <= w) {
        current[level] = 1;
        branch_and_bound(current, level + 1, best_value, best_solution, weight, value, n, w - weight[level]);
    }

    // Ramificação sem incluir o item atual
    current[level] = 0;
    branch_and_bound(current, level + 1, best_value, best_solution, weight, value, n, w);
}

// Resolve o problema da mochila 0-1 sem repetição com branch and bound
void bnb_knapsack(int w, int *result) {

    // Itera sobre os arquivos de entrada, cada um com um conjunto de itens
    for(int a = 1; a <= ENTRIES; a++) {

        // ----- Lê o arquivo de entrada

        int n = 0; // quantidade de itens no arquivo
        char file_path[20];

        // Formata o nome do arquivo
        sprintf(file_path, "input/%02d.txt", a);
        
        FILE *file = fopen(file_path, "r");

        // Retorna erro ao não encontrar o arquivo
        if(!file) {
            perror("Erro ao abrir o arquivo.");
            continue;
        }
        
        fscanf(file, "%d", &n);

        // ----- Aloca memória para a mochila

        // Evita problema de alocação vazia/negativa
        if(n <= 0) {
            fclose(file);
            continue;
        }
        
        int *weight = (int*)malloc(n * sizeof(int)); // array que armazena os pesos
        int *value = (int*)malloc(n * sizeof(int)); // array que armazena os valores
        
        // Retorna erro ao não encontrar alguns dos valores
        if(!weight || !value) {
            perror("Erro ao alocar memória.");
            fclose(file);
            return;
        }
        
        // ----- Lê os itens

        for(int i = 0; i < n; i++)
            fscanf(file, "%d %d", &weight[i], &value[i]); // armazena os pesos e valores
        
        fclose(file);
        
        // ----- Divide e poda

        // Aloca vetores para a solução corrente e a melhor solução encontrada
        int *current = (int *)calloc(n, sizeof(int));
        int *best_solution = (int *)calloc(n, sizeof(int));
        int best = 0;
        
        // Gera uma solução inicial (gulosa)
        initial_solution(0, w, n, current, weight);
        best = calc_value(n, current, value);
        copy_solution(n, best_solution, current);
        
        branch_and_bound(current, 0, &best, best_solution, weight, value, n, w);
        
        // Coloca a melhor solução encontrada no vetor resultado
        result[a - 1] = best;

        // ----- Libera a memória

        free(weight);
        free(value);
        free(current);
        free(best_solution);
    }
}
