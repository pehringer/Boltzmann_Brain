#include <stdlib.h>
#include <string.h>
#include <stdio.h>


struct NeurNet {
    double err;
    int lays;
    int *sizes;
    int len;
    float *vals;
    float *ins;
    float *outs;
};


struct Pop {
    int size;
    struct NeurNet *neurNets;
};


float Abs(float val) {
    return val >= 0 ? val : val * -1.0;
}

float RandFloat() {
    return (double) rand() / (double) RAND_MAX;
}


float RandFloatRange(float min, float max) {
    return RandFloat() * (max - min) + min;
}


int RandIntRange(int min, int max)
{
    return rand() % (max - min) + min;
}


const float* MatVecMult(const float *matA, const float *vecB, float *vecC, int n, int m) {
    for(int row = 0; row < n; row++) {
        *vecC = 0.0;
        const float *curB = vecB;
        for(int col = 0; col < m; col++) {
            *vecC += *matA * *curB;
            matA++;
            curB++;
        }
        vecC++;
    }
    return matA;
}


const float* VecVecAdd(const float *vecA, const float *vecB, float *vecC, int n) {
    for(int idx = 0; idx < n; idx++) {
        *vecC = *vecA + *vecB;
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
}


const float* ForProp(struct NeurNet n, const float *ins) {
    const float *curVals = n.vals;
    curVals = MatVecMult(curVals, ins, n.outs, n.sizes[1], n.sizes[0]);
    curVals = VecVecAdd(curVals, n.outs, n.ins, n.sizes[1]);
    VecReLU(n.ins, n.sizes[1]);
    for(int l = 2; l < n.lays; l++) {
        curVals = MatVecMult(curVals, n.ins, n.outs, n.sizes[l], n.sizes[l-1]);
        curVals = VecVecAdd(curVals, n.outs, n.ins, n.sizes[l]);
        VecReLU(n.ins, n.sizes[l]);
    }
    return n.ins;
}


float FitFunc(struct NeurNet n, const float *ins, const float *expOuts, int num) {
    n.err = 0.0;
    for(int i = 0; i < num; i++) {
        const float *outs = ForProp(n, ins);
        for(int j = 0; j < n.sizes[n.lays-1]; j++) {
            n.err += Abs(*expOuts - *outs);
            expOuts++;
            outs++;
        }
        ins += n.sizes[0];
    }
    return n.err;
}


struct NeurNet NewNeurNet(const int* sizes, int lays) {
    struct NeurNet n;
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
        n.outs[i] = RandFloatRange(-1.0, 1.0);
    }
    return n;
}


void DeleteNeurNet(struct NeurNet n) {
    free(n.sizes);
    free(n.vals);
    free(n.ins);
    free(n.outs);
}


struct Pop NewPop(int number, const int* sizes, int lays) {
    struct Pop p;
    p.size = number;
    p.neurNets = malloc(sizeof(struct NeurNet) * number);
    for(int i = 0; i < number; i++) {
        p.neurNets[i] = NewNeurNet(sizes, lays);
    }
    return p;
}


void DeletePop(struct Pop p) {
    for(int i = 0; i < p.size; i++) {
        DeleteNeurNet(p.neurNets[i]);
    }
    free(p.neurNets);
}


void main() {
    int lays = 3;
    int sizes[3] = {2, 2, 1};
    struct NeurNet net = NewNeurNet(sizes, lays);
    float vals[9] = {0.680375, 0.211234, 0.566198, 0.596880, 0.823295, 0.604897, 0.329554, 0.536459, 0.444451};
    net.vals = vals;
    float ins[8] = {0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0};
    float expOuts[4] = {0.0, 1.0, 1.0, 0.0};
    printf("For Prop: %f\n", *ForProp(net, ins));
    printf("For Prop: %f\n", *ForProp(net, ins + 2));
    printf("For Prop: %f\n", *ForProp(net, ins + 4));
    printf("For Prop: %f\n", *ForProp(net, ins + 6));
    printf("Fit Func: %f\n", FitFunc(net, ins, expOuts, 4));
}







