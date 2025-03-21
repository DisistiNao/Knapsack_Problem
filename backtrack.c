#include "backtrack.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_ITEMS 1000
#define MAX_WEIGHT 1000
int memo[MAX_ITEMS][MAX_WEIGHT];

// Resolve o problema da mochila 0-1 sem repetição com backtrack
void backtrack_knapsack(int w, int *result) {
    for (int a = 1; a <= 20; a++) {
        int n = 0;
        char fp[20];
        sprintf(fp, "Input/%02d.txt", a);

        FILE* file = fopen(fp, "r");
        if (!file) {
            perror("Erro ao abrir o arquivo");
            continue; // Skip to the next file if the current one cannot be opened
        }

        fscanf(file, "%d", &n);
        printf("File: %s, Read n = %d\n", fp, n);

        int *weigh = (int *)malloc(n * sizeof(int));
        int *value = (int *)malloc(n * sizeof(int));

        if (!weigh || !value) {
            perror("Erro ao alocar memória");
            fclose(file);
            return; // Exit the function if memory allocation fails
        }

        for (int i = 0; i < n; i++) {
            fscanf(file, "%d %d", &weigh[i], &value[i]);
        }
        fclose(file);

        memset(memo, -1, sizeof(memo));
        int maxValue = backtrack(w, weigh, value, n, 0, 0, 0);
        printf("Valor máximo com backtrack = %d\n", maxValue);

        free(weigh);
        free(value);
    }
}

// Função backtrack
int backtrack(int W, int wt[], int val[], int n, int index, int current_weight) {
    // Base case: if all items are processed or the knapsack is full
    if (index == n || current_weight >= W) {
        return 0;
    }

    // Check if the result is already computed
    if (memo[index][current_weight] != -1) {
        return memo[index][current_weight];
    }

    // Do not include the current item
    int withoutItem = backtrack(W, wt, val, n, index + 1, current_weight);

    // Include the current item (if it fits)
    int withItem = 0;
    if (current_weight + wt[index] <= W) {
        withItem = val[index] + backtrack(W, wt, val, n, index + 1, current_weight + wt[index]);
    }

    // Store the result in the memoization table
    memo[index][current_weight] = (withoutItem > withItem) ? withoutItem : withItem;

    return memo[index][current_weight];
}
