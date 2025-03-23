#include "dynamic_prog.h"
#include <stdio.h>
#include <stdlib.h>

// Resolve o problema da mochila 0-1 sem repetição com programação dinâmica,
// onde w é a capacidade máxima da mochila
void dynamic_knapsack(int w, int *result) {
    
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

        int *weigh = (int*)malloc(n * sizeof(int)); // array que armazena os pesos
        int *value = (int*)malloc(n * sizeof(int)); // array que armazena os valores

        // Retorna erro ao não encontrar alguns dos valores
        if(!weigh || !value) {
            perror("Erro ao alocar memória.");
            fclose(file);
            return;
        }

        // ----- Lê os itens

        for(int i = 1; i <= n; i++) 
            fscanf(file, "%d %d", &weigh[i-1], &value[i-1]); // armazena os pesos e valores

        fclose(file);

        // ----- Inicia a matriz de programação dinâmica
        
        // Matriz k com dimensões (n+1)x(w+1)
    
        int **k = (int**)malloc((n + 1) * sizeof(int*));

        for(int i = 0; i <= n; i++)
            k[i] = (int *)calloc(w + 1, sizeof(int)); // inicializa com zero

        // ----- Preenche a matriz de programação dinâmica

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= w; j++) {
                // Se o peso do item atual for maior do que a capacidade atual
                if(weigh[i-1] > j)
                    k[i][j] = k[i-1][j];
                // Caso contrário
                else {
                    // Busca o máximo entre não incluir o item e incluir o item
                    if(k[i-1][j] >= k[i-1][j-weigh[i-1]] + value[i-1]) 
                        k[i][j] = k[i-1][j];
                    else
                        k[i][j] = k[i-1][j-weigh[i-1]] + value[i-1];
                }
            }
        }

        // Armazena o resultado
        result[a-1] = k[n][w];
        // printf("%d\n", result[a-1]);
        
        // ----- Libera a memória

        for(int i = 0; i <= n; i++)
                free(k[i]);
            free(k);
            free(weigh);
            free(value);
    }
    return;
}
