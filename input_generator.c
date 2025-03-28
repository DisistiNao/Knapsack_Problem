#include "input_generator.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Gera arquivos de entrada para o problema da mochila 0-1
void generator(int n) {
    
    srand(time(NULL));
    
    // Gera os arquivos de entrada de acordo com o valor definido em ENTRIES
    for(int i = 1; i <= ENTRIES; i++) {

        // Formata o nome do arquivo
        char filename[20];  
        sprintf(filename, "input/%02d.txt", i);
        
        // Abre o arquivo para escrita
        FILE *input;
        input = fopen(filename, "w+");
        
        // Escreve o número de itens no início do arquivo
        fprintf(input, "%d\n", n);
        
        // Gera pesos e valores aleatórios para cada item e escreve no arquivo
        for(int j = 0; j < n; j++)
            fprintf(input, "%d %d\n", 1 + rand() % MAX_WEIGH, 1 + rand() % MAX_VALUE);
        
        fclose(input);
    }

    return;
}
