#ifndef MATH_H
#define MATH_H

#include <stdlib.h>

int RandInt(int min, int max);

float RandFlo(float min, float max);

float* VecMatMul(float *res, const float *vec, const float *mat, int rows, int cols);

float* VecVecAdd(float *res, const float *vec, int len);

float* VecReLU(float *res, int len);

#endif
