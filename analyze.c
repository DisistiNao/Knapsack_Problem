#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <getopt.h>

#include "input_generator.h"
#include "dynamic_prog.h"
#include "backtrack.h"
#include "branch_and_bound.h"

/*
Uso:
    gcc -Wall -o prog analyze.c input_generator.c dynamic_prog.c backtrack.c branch_and_bound.c -lm
*/

int main(int argc, char *argv[]) {
    int result[20];
    int w = 100, n = 100;

    FILE *backtrack_file, *bnb_file, *dynamic_prog_file;

    clock_t start, end;
    double dif;

    // Define as opções longas
    static struct option long_options[] = {
        {"dynamic", no_argument, 0, 'd'},
        {"backtrack", no_argument, 0, 'b'},
        {"branch", no_argument, 0, 'r'},
        {0, 0, 0, 0} // Última entrada deve ser zerada
    };

    // Variáveis para controlar quais métodos executar
    int run_dynamic = 0;
    int run_backtrack = 0;
    int run_branch = 0;

    // ----- Parser das opções da linha de comando
    
    int opt;
    int option_index = 0;
    
    while((opt = getopt_long(argc, argv, "", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'd':
                run_dynamic = 1;
                break;
            case 'b':
                run_backtrack = 1;
                break;
            case 'r':
                run_branch = 1;
                break;
            default:
                fprintf(stderr, "Uso: %s [--dynamic] [--backtrack] [--branch]\n", argv[0]);
                return 1;
        }
    }

    // Se nenhuma flag for passada, executa todos os métodos
    if(!run_dynamic && !run_backtrack && !run_branch) {
        run_dynamic = 1;
        run_backtrack = 1;
        run_branch = 1;
    }

    // ----- Primeiro loop: varia n com w fixo

    backtrack_file = fopen("backtrack_results.txt", "a+");
    dynamic_prog_file = fopen("dynamic_results.txt", "a+");
    bnb_file = fopen("bnb_results.txt", "a+");

    for(int i = 0; i < 10; i++) {
        n = 10 * pow(2, i);
        generator(n);


        // Programação dinâmica
        if(run_dynamic) {
            start = clock();
            dynamic_knapsack(w, result);
            end = clock();
            dif = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Programação Dinâmica: %.6lf segundos para W = %d e N = %d\n", dif, w, n);

            fprintf(dynamic_prog_file, "%d %.6lf\n", n, dif);
            
        }

        // Backtrack
        if(run_backtrack) {
            start = clock();
            backtrack_knapsack(w, result);
            end = clock();
            dif = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Backtrack: %.6lf segundos para W = %d e N = %d\n", dif, w, n);

            fprintf(backtrack_file, "%d %.6lf\n", n, dif);
         
        }

        // Branch and bound
        if(run_branch) {
            start = clock();
            bnb_knapsack(w, result);
            end = clock();
            dif = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Branch and Bound: %.6lf segundos para W = %d e N = %d\n", dif, w, n);

            fprintf(bnb_file, "%d %.6lf\n", n, dif);

        }
    }

    fclose(backtrack_file);
    fclose(dynamic_prog_file);
    fclose(bnb_file);

    printf("\n");

    // ----- Segundo loop: varia w com n fixo

    n = 400;
    
    for(int i = 0; i < 10; i++) {
        w = 100 * pow(2, i);
        generator(n);

        // Programação dinâmica
        if(run_dynamic) {
            start = clock();
            dynamic_knapsack(w, result);
            end = clock();
            dif = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Programação Dinâmica: %.6lf segundos para W = %d e N = %d\n", dif, w, n);
        }

        // Backtrack
        if(run_backtrack) {
            start = clock();
            backtrack_knapsack(w, result);
            end = clock();
            dif = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Backtrack: %.6lf segundos para W = %d e N = %d\n", dif, w, n);
        }

        // Branch and bound
        if(run_branch) {
            start = clock();
            bnb_knapsack(w, result);
            end = clock();
            dif = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Branch and Bound: %.6lf segundos para W = %d e N = %d\n", dif, w, n);
        }
    }

    return 0;
}
