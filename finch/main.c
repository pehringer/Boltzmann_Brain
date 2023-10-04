#include <stdio.h>

#include "math.h"
#include "mutation.h"

void main(void) {
    float genome[8] = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};

    struct Individual i = {0.0, 8, genome};

    SegmentInversion(&i, 4, 8);
    for(int gene = 0; gene < 8; gene++) {
        printf("%f ", i.genome[gene]);
    }
    printf("\n");

}
