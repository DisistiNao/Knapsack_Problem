#ifndef BRANCH_AND_BOUND_H_
#define BRANCH_AND_BOUND_H_

// Quantidade de arquivos de entrada
#define ENTRIES 20

// Cria uma solução inicial para o problema da Mochila 0-1 sem repetição
// void initial_solution(int, int, int, int*, int*);

// 
// int calc_value(int, int, int);

// Resolve o problema da Mochila 0-1 sem repetição com branch-and-bound
void bb_knapsack(int, int*);

// 
// void branch_and_bound(int, int, int*, int*, int, int*, int);

#endif
