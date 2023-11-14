#include "math.h"

int RandInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

float RandFlo(float min, float max) {
    return (double) rand() / (double) RAND_MAX * (max - min) + min;
}

float MatSum(int rows, int cols, const float *mat) {
    int sum = 0.0;
    for(int i = 0; i < rows * cols; i++) {
        sum += mat[i];
    }
    return sum;
}

void MatAbs(int rows, int cols, const float *mat, float *res) {
    for(int i = 0; i < rows * cols; i++) {
        res[i] = mat[i];
        if(res[i] < 0.0) {
            res[i] *= -1;
        }
    }
}

void MatRLU(int rows, int cols, const float *mat, float *res) {
    for(int i = 0; i < rows * cols; i++) {
        res[i] = mat[i];
        if(res[i] < 0.0) {
            res[i] = 0.0;
        }
    }
}

void MatAdd(int rows, int cols, const float *matA, const float *matB, float *res) {
    for(int i = 0; i < rows * cols; i++) {
        res[i] = matA[i] + matB[i];
    }
}

void MatSub(int rows, int cols, const float *matA, const float *matB, float *res) {
    for(int i = 0; i < rows * cols; i++) {
        res[i] = matA[i] - matB[i];
    }
}

void MatMul(int rows, int cols,  const float *mat, const float *vec, float *res) {
    for(int i = 0; i < rows; i++) {
        res[i] = 0.0;
        for(int j = 0; j < cols; j++) {
            res[i] += mat[j] * vec[j];
        }
        mat += cols;
    }
}

