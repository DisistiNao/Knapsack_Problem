#ifndef BACKTRACK_H_
#define BACKTRACK_H_

typedef struct {
    int weight;
    int value;
    double ratio; 
} Item;

int backtrack(int W, Item items[], int n, int index, int current_weight, int current_value);

void backtrack_knapsack(int w, int *result);

#endif
