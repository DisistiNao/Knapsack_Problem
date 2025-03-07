#include <stdio.h>

#include "input_generator.h"
#include "dynamic_prog.h"

int main()
{
    int result[20], w = 100;
    int n = 100;

    generator(n);
    dynamic_knapsack(w, result);

    return 0;
}