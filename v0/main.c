#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* MATH CODE */

int RandomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

float RandomFloat(float min, float max) {
    return (double) rand() / (double) RAND_MAX * (max - min) + min;
}

/* MATRIX OPERATIONS */

float MatrixSummation(int rows, int columns, const float *matrix) {
    float sum = 0.0;
    for(int i = 0; i < rows * columns; i++) {
        sum += matrix[i];
    }
    return sum;
}

void MatrixReLU(int rows, int columns, const float *matrix, float *result) {
    for(int i = 0; i < rows * columns; i++) {
        result[i] = matrix[i];
        if(result[i] < 0.0) {
            result[i] = 0.0;
        }
    }
}

void MatrixAbsolute(int rows, int columns, const float *matrix, float* result) {
    for(int i = 0; i < rows * columns; i++) {
        result[i] = matrix[i];
        if(result[i] < 0.0) {
            result[i] *= -1;
        }
    }
}

void MatrixAddition(int rows, int columns, const float *matrix1, const float *matrix2, float *result) {
    for(int i = 0; i < rows * columns; i++) {
        result[i] = matrix1[i] + matrix2[i];
    }
}

void MatrixSubtraction(int rows, int columns, const float *matrix1, const float *matrix2, float *result) {
    for(int i = 0; i < rows * columns; i++) {
        result[i] = matrix1[i] - matrix2[i];
    }
}

void MatrixMultiplication(int rows, int columns, const float *matrix, const float *vector, float *result) {
    for(int i = 0; i < rows; i++) {
        result[i] = 0.0;
        for(int j = 0; j < columns; j++) {
            result[i] += matrix[j] * vector[j];
        }
	matrix += columns;
    }
}

/* MUTATE OPERATIONS */

void MutateAdjustment(int genes, float *genome, float min, float max) {
    int point = RandomInt(0, genes - 1);
    genome[point] += RandomFloat(min, max);
}

void MutateInversion(int genes, float *genome, int min, int max) {
    int range = RandomInt(min, max);
    int start = RandomInt(0, genes - range);
    int stop = start + range - 1;
    while(start <= stop) {
        float temp = genome[start];
        genome[start] = genome[stop];
        genome[stop] = temp;
	start++;
	stop--;
    }
}

void MutateSubstitution(int genes, float *genome, int min, int max) {
    int range = RandomInt(min, max);
    int start = RandomInt(0, genes - range);
    int stop = start + range - 1;
    int swap = RandomInt(0, genes - range);
    while(start <= stop) {
        float temp = genome[start];
        genome[start] = genome[swap];
        genome[swap] = temp;
        start++;
        swap++;
    }
}

void MutateRotation(int genes, float * genome , int min, int max) {
    int range = RandomInt(min, max);
    int rotate = RandomInt(0, range);
    int start = RandomInt(0, genes - range);
    int stop = start + range - 1;
    printf("range: %d  rotate: %d  start: %d  stop: %d\n", range, rotate, start, stop);
    while(rotate > 0) {
        int swap = start;
        int gene = genome[stop];
        while(swap <= stop) {
            int temp = genome[swap];
            genome[swap] = gene;
            gene = temp;
            swap++;
        }
        rotate--;
    }
}

/* CROSSOVER OPERATIONS

void CrossoverUniform(int genes, const float *genome1, const float *genome2, float *result);

void CrossoverAverage(int genes, const float *genome1, const float *genome2, float *result);

void CrossoverPoint(float *offspringGenome, float *maleGenome, float *femaleGenome, int genes);

*/

/* NETWORK CODE

struct Network{
    int   depth;
    int   length;
    int   *width;
    float *parameter;
    float *input;
    float *output;
};

struct Network NetworkAllocate(int depth, const int *width) {
    struct Network n;
    n.depth = depth;
    n.length = 0;
    int max = width[0];
    for(int i = 1; i < depth; i++) {
        if(width[i] > max) {
            max = width[i];
        }
	n.length += width[i] * width[i-1] + width[i];
    }
    n.width = malloc(sizeof(int) * depth + sizeof(float) * (n.length + max + max));
    memcpy(n.width, width, sizeof(int) * depth);
    n.parameter = n.width + depth;
    n.inpput = n.parameter + n.length;
    n.output = n.input + max;
    return n;
}

void NetworkDeallocate(struct Network n) {
    free(n.wid);
}

void NetworkInitialize(struct Network n, float min, float max) {
    for(int i = 0; i < n.length; i++) {
        n.parameter[i] = RandomFloat(min, max);
    }
}

const float* NetworkPropagation(struct Network n, const float *input) {
    memcpy(n.output, input, sizeof(float) * n.width[0]);
    float *parameter = n.parameter;
    for(int i = 1; i < n.depth; i++) {
        MatrixMultiplication(n.width[i], n.width[i-1], parameter, n.output, n.input);
        parameter += n.width[i] * n.width[i-1];
        MatrixAddition(1, n.width[i], parameter, n.input, n.output);
        parameter += n.width[i];
        MatrixReLU(1, n.width[i], n.output, n.output);
    }
    return n.output
}

float NetworkError(struct Network n, const float *expected) {
    MatrixSubtraction(1, n.width[n.depth-1], expected, n.output, n.input);
    MatrixAbsolute(1, n.width[n.depth-1], n.input, n.input);
    return MatrixSummation(1, n.width[n.depth-1], n.input);
}

*/

void main(void) {
    float m1[6] = {
        1.00, 1.01, 1.02,
        1.10, 1.11, 1.12,
    };
    float m2[6] = {
        2.00, 2.01, 2.02,
        2.10, 2.11, 2.12,
    };
    float m3[6] = {
        3.00, 3.01, 3.02,
        3.10, 3.11, 3.12,
    };
    /*
    float g[10] = {
        0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9,
    };
    */

    for(int i = 0; i < 128; i++) {
        float g[10] = {
            0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9,
        };
        MutateRotation(10, g, 10, 10);
        for(int j = 0; j < 10; j++) {
            printf("%f,", g[j]);
        }
        printf("\n\n");
    }
}
