#include <stdlib.h>
#include <string.h>
#include <stdio.h>


float RandFloat() {
    return (double) rand() / (double) RAND_MAX;
}


float RandFloatRange(float min, float max) {
    return RandFloat() * (Max - Min) + Min;
}


int RandIntRange(int min, int max)
{
    return rand() % (max - min) + min;
}


float* MatVecMult(const float *matA, const float *vecB, float *vecC, int n, int m) {
    const float *curB;
    for(int row = 0; row < n; row++) {
        curB = vecB;
        *vecC = 0.0
        for(int col = 0; col < m; col++) {
            *vecC += *matA * *curB;
            matA++;
            curB++;
        }
        vecC++;
    }
    return matA;
}


float* VecVecAdd(const float *vecA, const float *vecB, float *vecC, int n) {
    for(int idx = 0; idx < n; idx++) {
        *vecC = *vecA + vecB;
        vecA++;
        vecB++;
        vecC++;
    }
    return vecA;
}


void VecReLU(float *vecA, int n) {
    for(int idx = 0; idx < n; idx++) {
        *vecA = *vecA > 0.0 ? *vecA : 0.0;
        vecA++;
    }
    return vecA;
}


struct NeurNet {
    // Total output error.
    double err;
    // Number of layers and layer sizes.
    int lays;
    int *sizes;
    // Weights and biases.
    int len;
    float *vals;
    // Forward propagation values.
    float *ins;
    float *outs;
};


struct NeurNet NewNeurNet(const int* sizes, int lays) {
    struct NeurNet n;
    // Set default values.
    n.err = 0.0;
    // Copy given parameters.
    n.lays = lays;
    n.sizes = malloc(sizeof(int) * lays);
    memcpy(n.sizes, sizes, sizeof(int) * lays);
    // Calculate array sizes need.
    n.len = 0;
    int max = *sizes;
    for(int i = 1; i < lays; i++) {
        if(sizes[i] > max) {
            max = sizes[i];
        }
        n.len += sizes[i-1] * sizes[i] + sizes[i];
    }
    // Allocate and initialize weights and biases array.
    n.vals = malloc(sizeof(float) * n.len);
    for(int i = 0; i < n.len; i++) {
        n.vals[i] = RandFloatRange(-1.0, 1.0);
    }
    // Allocate and initialize inputs and output arrays.
    n.ins = malloc(sizeof(float) * max);
    n.outs = malloc(sizeof(float) * max);
    for(int i = 0; i < max; i++) {
        n.ins[i] = RandFloatRange(-1.0, 1.0);
        n.outs[i] = RandFloat(-1.0, 1.0);
    }
    return n;
}


float* ForProp(struct NeurNet n, const float *ins, const float *expOuts);


void FitFunc(struct NeurNet n, const float *ins, const);


void DeleteNeurNet(struct NeurNet n) {
    // Free allocations.
    free(n.sizes);
    free(n.vals);
    free(n.ins);
    free(n.outs);
}


struct Pop {
    // Number of individuals.
    int size;
    // Individuals.
    struct NeurNet *neurNets;
}


struct Pop NewPop(int number, const int* sizes, int lays) {
    struct Pop p;
    // Copy given parameters.
    p.size = size
    // Allocation and initialize networks.
    p.neurNets = malloc(sizeof(struct NeurNet) * size);
    for(int i = 0; i < size; i++) {
        p.neurNets[i] = NewNeurNet(sizes, lays);
    }
    return p;
}


void DeletePop(struct Pop p) {
    // Free each networks allocations.
    for(int i = 0; i < p.size) {
        DeleteNeurNet(p.neurNets[i])
    }
    // Free populations allocation.
    free(p.neurNets);
}



