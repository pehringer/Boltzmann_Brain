#include <stdio.h>

#include "math.h"

void main(void) {
    float matA[6] = {
        0.0, -1.1, 2.2,
        3.3, 4.4, 5.5,
    };
    float matB[6] = {
        6.6, -7.7, 8.8,
        -9.9, 10.10, -11.11,
    };
    float vec[3] = {
        12.12, 13.13, 14.14,
    };
    float resMat[6] = {
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
    };
    float resVec[2] = {
        0.0, 0.0,
    };
    MatMul(2, 3, matB, vec, resVec);
    printf("Op: ");
    for(int i = 0; i < 2; i++) {
        printf("%f, ", resVec[i]);
    }
    printf("\n");

}
