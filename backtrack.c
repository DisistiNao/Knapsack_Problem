#include "backtrack.h"
#include <stdio.h>
#include <stdlib.h>

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

        int maxValue = backtrack(w, weigh, value, n, 0, 0, 0);
        printf("Valor máximo com backtrack = %d\n", maxValue);

        free(weigh);
        free(value);
    }
}

int backtrack(int W, int wt[], int val[], int n, int index, int current_weight, int current_value) {
    // Debugging print statement
    //printf("Index: %d, Current Weight: %d, Current Value: %d\n", index, current_weight, current_value);

    // Base case: if all items are processed or the knapsack is full
    if (index == n || current_weight >= W) {
        return current_value;
    }

    // Do not include the current item
    int withoutItem = backtrack(W, wt, val, n, index + 1, current_weight, current_value);

    // Include the current item (if it fits)
    int withItem = 0;
    if (current_weight + wt[index] <= W) {
        withItem = backtrack(W, wt, val, n, index + 1, current_weight + wt[index], current_value + val[index]);
    }

    // print("teste");
    // Tirar gambiarra
    // Return the maximum value between including or excluding the item
    if(withoutItem > withItem)
        return withoutItem;
    return withItem;
    
    return (withoutItem > withItem) ? withoutItem : withItem;
}
