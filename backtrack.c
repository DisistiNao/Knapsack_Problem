#include <stdio.h>
#include <stdlib.h>

#include "backtrack.h"

// Compara dois itens pelo peso
int compare_items(const void *a, const void *b) {
    Item *item_a = (Item*)a;
    Item *item_b = (Item*)b;

    if(item_a->weight > item_b->weight) return -1; // ordem decrescente de peso
    if(item_a->weight < item_b->weight) return 1;
    return 0;
}

// Resolve o problema da mochila 0-1 sem repetição com backtrack
void backtrack_knapsack(int w, int *result) {
    
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

        // Print de teste
        printf("File: %s, Read n = %d\n", file_path, n);
        
        // ----- Aloca memória para a mochila

        // Evita problema de alocação vazia/negativa
        if(n <= 0) {
            fclose(file);
            continue;
        }

        Item *items = (Item*)malloc(n * sizeof(Item));

        // ----- Lê os itens

        for(int i = 0; i < n; i++) {
            fscanf(file, "%d %d", &items[i].weight, &items[i].value);
        }
        fclose(file);
        
        // ----- Backtrack
        
        // Ordena de forma decrescente de acordo com os pesos
        qsort(items, n, sizeof(Item), compare_items);

        int maxValue = backtrack(w, items, n, 0, 0, 0);

        // Print de teste
        printf("Valor máximo com backtrack = %d\n", maxValue);

        // ----- Libera a memória

        free(items);
    }
}

// Função backtrack
int backtrack(int W, Item items[], int n, int index, int current_weight, int current_value) {
    
    // Caso base, nenhum item ou mochila cheia (peso)
    if (index == n || current_weight >= W) {
        return current_value;
    }

    // Recursão sem adicionar o item
    int withoutItem = backtrack(W, items, n, index + 1, current_weight, current_value);

    // Recursão adicionando o item (verifica se cabe antes)
    int withItem = 0;
    if (current_weight + items[index].weight <= W) {
        withItem = backtrack(W, items, n, index + 1, current_weight + items[index].weight, current_value + items[index].value);
    }

    // Escolhe o maior valor, se foi com ou sem a inclusão do item
    if(withoutItem > withItem)
        return withoutItem;
    else
        return withItem;
}
