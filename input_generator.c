#include "input_generator.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void generator(int n) {
    int max_weigh = 30, max_value = 100;
    
    srand(time(NULL));
    
    for(int i = 1; i <= 20; i++) {
        char filename[20];  
        sprintf(filename, "Input/%02d.txt", i);
        
        FILE *input;
        input = fopen(filename, "w+");
        
        fprintf(input, "%d\n", n);
        
        for(int j = 0; j < n; j++)
            fprintf(input, "%d %d\n", 1 + rand() % max_weigh, 1 + rand() % max_value);
        
        fclose(input);
    }

    return;
}
