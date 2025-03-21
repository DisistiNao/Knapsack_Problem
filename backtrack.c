#include <stdio.h>
#include <stdlib.h>

#include "backtrack.h"

int compare_items(const void *a, const void *b) {
    Item *item_a = (Item *)a;
    Item *item_b = (Item *)b;

    if (item_a->ratio > item_b->ratio) return -1; // Sort in descending order
    if (item_a->ratio < item_b->ratio) return 1;
    return 0;
}

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

        Item *items = (Item *)malloc(n * sizeof(Item));

        for (int i = 0; i < n; i++) {
            fscanf(file, "%d %d", &items[i].weight, &items[i].value);
        }
        fclose(file);
        qsort(items, n, sizeof(Item), compare_items);


        FILE* backtrack_file = fopen("backtrack_results", "a+");

        int maxValue = backtrack(w, items, n, 0, 0, 0);
        printf("Valor máximo com backtrack = %d\n", maxValue);

        free(items);
        
    }
}

int backtrack(int W, Item items[], int n, int index, int current_weight, int current_value) {
    // Base case: if all items are processed or the knapsack is full
    if (index == n || current_weight >= W) {
        return current_value;
    }

    // Do not include the current item
    int withoutItem = backtrack(W, items, n, index + 1, current_weight, current_value);

    // Include the current item (if it fits)
    int withItem = 0;
    if (current_weight + items[index].weight <= W) {
        withItem = backtrack(W, items, n, index + 1, current_weight + items[index].weight, current_value + items[index].value);
    }

    // Return the maximum value between including or excluding the item
    return (withoutItem > withItem) ? withoutItem : withItem;
}
