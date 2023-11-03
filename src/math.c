#include "math.h"

int RandInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

float RandFlo(float min, float max) {
    return (double) rand() / (double) RAND_MAX * (max - min) + min;
}

/*
Parameters:
res - Vector that holds matrix-vector product.
vec - Vector to be multiplied.
mat - Matrix to be multiplied.
rows - Rows of mat / length of res.
cols - Columns of mat / length of vec.
Returns:
Pointer to the end of mat.
*/
float* VecMatMul(float *res, const float *vec, const float *mat, int rows, int cols) {
    for(int m = 0; m < rows; m++) {
        res[m] = 0.0
        for(int n = 0; n < cols; n++) {
            res[m] += mat[m * cols + n] * vec[n];
        }
    }
    return mat + rows * cols;
}

/*
Parameters:
res - Vector that holds vector-vector sum.
vec - Vector to be added to res.
len - Length of res and vec.
Returns:
Pointer to the end of vec.
*/
float* VecVecAdd(float *res, const float *vec, int len) {
    for(int n = 0; n < len; n++) {
        res[n] += vec[n];
    }
    return vec + len;
}

/*
Parameters:
res - Vector that holds vector ReLU.
len - Length of res.
Returns:
Pointer to the end of res.
*/
float* VecReLU(float *res, int len) {
    for(int n = 0; n < len; n++) {
        if(res[n] < 0.0) {
            res[n] = 0.0;
        }
    }
    return res + len;
}
