#include "math.h"

float Abs(float val) {
    return val < 0.0 ? val * -1.0 : val;
}

float ReLU(float val) {
    return val < 0.0 ? 0.0 : val;
}

float VecSum(float *res, int len) {
    float sum = 0.0;
    for(int n = 0; n < len; n++) {
        sum += res[n];
    }
    return sum;
}

void VecElemWise(float *res, int len, float (*oper)(float)) {
    for(int n = 0; n < len; n++) {
        res[n] = oper(res[n]);
    }
}

void VecVecAdd(float *res, const float *vec, int len) {
    for(int n = 0; n < len; n++) {
        res[n] += vec[n];
    }
}

void VecVecSub(float *res, const float *vec, int len) {
    for(int n = 0; n < len; n++) {
        res[n] -= vec[n];
    }
}

void MatVecMul(float *res, const float *mat, const float *vec, int rows, int cols) {
    for(int m = 0; m < rows; m++) {
        res[m] = 0.0;
        for(int n = 0; n < cols; n++) {
            res[m] += mat[m * cols + n] * vec[n];
        }
    }
}

int RandInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

float RandFlo(float min, float max) {
    return (double) rand() / (double) RAND_MAX * (max - min) + min;
}
