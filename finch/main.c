#include <stdio.h>

#include "math.h"
#include "mutation.h"
#include "crossover.h"

#define GENES 1

float male[GENES]; //= {1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9};
float female[GENES]; //= {2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9};
float offspring[GENES];

void resetOffspring(void) {
    for(int gene = 0; gene < GENES; gene++) {
        offspring[gene] = gene / 10.0;
    }
}

void printOffspring(void) {
    for(int gene = 0; gene < GENES; gene++) {
        printf("%f ", offspring[gene]);
    }
    printf("\n");
}


void main(void) {
    for(int i = 0; i < 32; i++) {
        resetOffspring();
        MutationPointChange(offspring, GENES, 0.1, 0.5);
        printOffspring();
    }
}
