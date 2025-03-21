#ifndef BRANCH_AND_BOUND_H_
#define BRANCH_AND_BOUND_H_

// Quantidade de arquivos de entrada
#define ENTRIES 20

// Cria uma solução inicial (gulosa) para a mochila 0-1
void initial_solution(int, int, int, int*, int*);

// Calcula o valor total da solução da mochila 0-1
int calc_value(int, int*, int*);

// Copia uma solução do vetor origem para o vetor destino
void copy_solution(int, int*, int*);

// Função branch and bound com poda baseada em limite guloso
void branch_and_bound(int*, int, int*, int*, int*, int*, int, int);

// Resolve o problema da mochila 0-1 sem repetição com branch and bound
void bb_knapsack(int, int*);

#endif
