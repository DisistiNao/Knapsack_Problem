#ifndef BACKTRACK_H_
#define BACKTRACK_H_

// Quantidade de arquivos de entrada
#define ENTRIES 20

// Definição da estrutura do item
typedef struct {
    int weight;
    int value;
} Item;

// Compara dois itens pelo peso
int compare_items(const void*, const void*);

// Função backtrack
int backtrack(int, Item*, int, int, int, int);

// Resolve o problema da mochila 0-1 sem repetição com backtrack
void backtrack_knapsack(int, int*);

#endif
