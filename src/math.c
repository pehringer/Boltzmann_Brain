#include "math.h"

float Abs(float value) {
    return value < 0.0 ? value * -1.0 : value;
}

float ReLU(float value) {
    return value < 0.0 ? 0.0 : value;
}

float VecSum(float *result, int length) {
    float sum = 0.0;
    for(int n = 0; n < length; n++) {
        sum += result[n];
    }
    return sum;
}

void VecElemWise(float *result, int length, float (*operation)(float)) {
    for(int n = 0; n < length; n++) {
        result[n] = operation(result[n]);
    }
}

void VecVecAdd(float *result, const float *vector, int length) {
    for(int n = 0; n < length; n++) {
        result[n] += vector[n];
    }
}

void VecVecSub(float *result, const float *vector, int length) {
    for(int n = 0; n < length; n++) {
        result[n] -= vector[n];
    }
}

void MatVecMul(float *result, const float *matrix, const float *vector, int rows, int columns) {
    for(int m = 0; m < rows; m++) {
        result[m] = 0.0;
        for(int n = 0; n < columns; n++) {
            result[m] += matrix[m * columns + n] * vector[n];
        }
    }
}

int RandInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

float RandFlo(float min, float max) {
    return (double) rand() / (double) RAND_MAX * (max - min) + min;
}
