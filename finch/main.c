#include <stdio.h>

#include "math.h"
#include "mutation.h"

#define GENES 8

float genome[GENES];

void resetGenome(void) {
    for(int gene = 0; gene < GENES; gene++) {
        genome[gene] = gene + gene / 10.0;
    }
}

void printGenome(void) {
    for(int gene = 0; gene < GENES; gene++) {
        printf("%f ", genome[gene]);
    }
    printf("\n");
}


void main(void) {
    for(int i = 0; i < 32; i++) {
        resetGenome();
        MutationDuplication(genome, GENES, 1, 3);
        printGenome();
    }
}
