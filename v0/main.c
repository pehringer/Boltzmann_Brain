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

/* NETWORK CODE */

struct Network{
    int   depth;
    int   length;
    int   *widths;
    float *parameters;
    float *inputs;
    float *outputs;
};

struct Network NetworkAllocate(int depth, const int *widths) {
    struct Network n;
    n.depth = depth;
    n.length = 0;
    int max = widths[0];
    for(int i = 1; i < depth; i++) {
        if(widths[i] > max) {
            max = widths[i];
        }
	n.length += widths[i] * widths[i - 1] + widths[i];
    }
    n.widths = malloc(sizeof(int) * depth + sizeof(float) * (n.length + max + max));
    memcpy(n.widths, widths, sizeof(int) * depth);
    n.parameters = (float*) (n.widths + depth);
    for(int i = 0; i < n.length; i++) {
        n.parameters[i] = RandomFloat(-1.0, 1.0);
    }
    n.inputs = n.parameters + n.length;
    n.outputs = n.inputs + max;
    return n;
}

void NetworkDeallocate(struct Network n) {
    free(n.widths);
}

const float* NetworkPropagation(struct Network n, const float *inputs) {
    memcpy(n.outputs, inputs, sizeof(float) * n.widths[0]);
    float *parameters = n.parameters;
    for(int i = 1; i < n.depth; i++) {
        MatrixMultiplication(n.widths[i], n.widths[i-1], parameters, n.outputs, n.inputs);
        parameters += n.widths[i] * n.widths[i-1];
        MatrixAddition(1, n.widths[i], parameters, n.inputs, n.outputs);
        parameters += n.widths[i];
        MatrixReLU(1, n.widths[i], n.outputs, n.outputs);
    }
    return n.outputs;
}

float NetworkError(struct Network n, const float *expected) {
    MatrixSubtraction(1, n.widths[n.depth - 1], expected, n.outputs, n.inputs);
    MatrixAbsolute(1, n.widths[n.depth - 1], n.inputs, n.inputs);
    return MatrixSummation(1, n.widths[n.depth - 1], n.inputs);
}

/* Tests Code */

struct Tests {
    int pairs;
    const float *inputs;
    const float *outputs;
};

/* Individual Code */

struct Individual {
    float fitness;
    struct Network n;
};

int IndividualCompare(const void *l, const void *r) {
    float result = ((struct Individual*) l)->fitness - ((struct Individual*) r)->fitness;
    if(result < 0.0) {
        return -1;
    }
    if(result > 0.0) {
        return 1;
    }
    return 0.0;
}

struct Individual IndividualAllocate(int depth, const int *widths) {
    struct Individual i;
    i.fitness = 0.0;
    i.n = NetworkAllocate(depth, widths);
    return i;
}

void IndividualDeallocate(struct Individual i) {
    NetworkDeallocate(i.n);
}

float IndividualFitness(struct Individual i, struct Tests t) {
    i.fitness = 0.0;
    for(int p = 0; p < t.pairs; p++) {
        NetworkPropagation(i.n, t.inputs);
        t.inputs += i.n.widths[0];
        i.fitness += NetworkError(i.n, t.outputs);
        t.outputs += i.n.widths[i.n.depth - 1];
    }
    return i.fitness /= t.pairs;
}

void IndividualMutation(struct Individual i, float min, float max) {
    int gene = RandomInt(0, i.n.length);
    i.n.parameters[gene] = RandomFloat(min, max);
}

void IndividualCrossover(struct Individual i1, struct Individual i2, struct Individual result) {
    for(int p = 0; p < result.n.length; p++) {
        if(RandomInt(0, 1)) {
            result.n.parameters[p] = i1.n.parameters[p];
        } else {
            result.n.parameters[p] = i2.n.parameters[p];
        }
    }
}

/* Population Code */

struct Population {
    int size;
    struct Individual *is;
};

struct Population PopulationAllocate(int size, int depth, const int *widths) {
    struct Population p;
    p.size = size;
    p.is = malloc(sizeof(struct Individual) * size);
    for(int i = 0; i < size; i++) {
        p.is[i] = IndividualAllocate(depth, widths);
    }
    return p;
}

void PopulationDeallocate(struct Population p) {
    for(int i = 0; i < p.size; i++) {
        IndividualDeallocate(p.is[i]);
    }
    free(p.is);
}

void PopulationFitness(struct Population p, struct Tests t) {
    for(int i = 0; i < p.size; i++) {
        p.is[i].fitness = IndividualFitness(p.is[i], t);
    }
}

void PopulationSelection(struct Population p) {
    qsort(p.is, p.size, sizeof(struct Individual), IndividualCompare);
}

void PopulationCrossover(struct Population p) {
    for(int i = p.size / 2; i < p.size; i++) {
        int i1 = RandomInt(0, p.size / 2);
        int i2 = RandomInt(0, p.size / 2);
        IndividualCrossover(p.is[i1], p.is[i2], p.is[i]);
    }
}

void PopulationMutation(struct Population p, float min, float max) {
    for(int i = p.size / 2; i < p.size; i++) {
        IndividualMutation(p.is[i], min, max);
    }
}


void main(void) {
    int gen = 256;
    int PopSiz = 256;
    float MutMin = -0.5;
    float MutMax = 0.5;

    int NetDep = 3;
    int NetWid[3] = {2, 2, 1};

    float Inp[8] = {0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0};
    float OrOut[4] = {0.0, 1.0, 1.0, 1.0};
    float NorOut[4] = {1.0, 0.0, 0.0, 0.0};
    float XorOut[4] = {0.0, 1.0, 1.0, 0.0};
    float AndOut[4] = {0.0, 0.0, 0.0, 1.0};

    //struct Network n = NetworkAllocate(NetDep, NetWid);
    //NetworkDeallocate(n);

    struct Tests t = (struct Tests) {4, Inp, XorOut};
    struct Population p = PopulationAllocate(PopSiz, NetDep, NetWid);
    for(int i = 0; i < gen; i++) {
        PopulationFitness(p, t);
	PopulationSelection(p);
        PopulationCrossover(p);
        PopulationMutation(p, MutMin, MutMax);
        printf("Gen: %d, Err: %f\n", i, p.is[0].fitness);
    }
    PopulationDeallocate(p);
}
