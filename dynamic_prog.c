#include "dynamic_prog.h"

#include <stdio.h>
#include <stdlib.h>

void dynamic_knapsack(int w, int *result) {
    for(int a = 1; a <= 20; a++) {
        int n = 0;
        char fp[20];  
        sprintf(fp, "Input/%02d.txt", a);
        
        FILE* file = fopen (fp, "r");
        
        if (!file) { 
            perror("Erro ao abrir o arquivo");
            continue;
        }

        fscanf (file, "%d", &n);
        
        int *weigh = (int *)malloc(n * sizeof(int));
        int *value = (int *)malloc(n * sizeof(int));

        if (!weigh || !value) {
            perror("Erro ao alocar memória");
            fclose(file);
            return;
        }

        for(int i = 1; i <= n; i++) 
            fscanf(file, "%d %d", &weigh[i-1], &value[i-1]);

        fclose (file);
        
        int **k = (int **)malloc((n + 1) * sizeof(int *));
        for (int i = 0; i <= n; i++)
            k[i] = (int *)calloc(w + 1, sizeof(int));

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= w; j++) {
                if(weigh[i-1] > j)
                    k[i][j] = k[i-1][j];
                else {
                    if(k[i-1][j] >= k[i-1][j-weigh[i-1]] + value[i-1]) 
                        k[i][j] = k[i-1][j];
                    else
                        k[i][j] = k[i-1][j-weigh[i-1]] + value[i-1];
                }
            }
        }
        result[a-1] = k[n][w];
        printf("%d\n", result[a-1]);
        
        for (int i = 0; i <= n; i++)
                free(k[i]);
            free(k);
            free(weigh);
            free(value);
    }
    
    return;
}

// int main() {
//     int result[20], w = 100;

//     dynamic_knapsack(w, result);

//     return 0;
// }