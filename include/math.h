#ifndef MATH_H
#define MATH_H

#include <stdlib.h>

// Math Functions

/*
Parameters:
val - Value.
Returns:
Absolute value of val.
*/
float Abs(float val);

/*
Parameters:
val - Value.
Returns:
Rectified linear unit of val.
*/
float ReLU(float val);

// Matrix & Vector Operations

/*
Parameters:
res - Vector that holds element for summation.
len - Length of res.
Returns:
Summation of res.
*/
float VecSum(float *res, int len);

/*
Parameters:
res - Vector that holds element-wise result.
len - Length of res.
oper - Operation to be performed on each element of res.
*/
void VecElemWise(float *res, int len, float (*oper)(float));

/*
Parameters:
res - Vector that holds vector-vector sum.
vec - Vector to be added to res.
len - Length of res and vec.
*/
void VecVecAdd(float *res, const float *vec, int len);

/*
Parameters:
res - Vector that holds vector-vector difference.
vec - Vector to be subtracted from res.
len - Length of res and vec.
*/
void VecVecSub(float *res, const float *vec, int len);

/*
Parameters:
res - Vector that holds matrix-vector product.
vec - Vector to be multiplied.
mat - Matrix to be multiplied.
rows - Rows of mat / length of res.
cols - Columns of mat / length of vec.
*/
void MatVecMul(float *res, const float *mat, const float *vec, int rows, int cols);

// Miscellaneous

/*
Parameters:
min - Minimum value to be randomly generated.
max - Maximum value to be randomly generated.
Returns:
Randomly generated value between min and max (inclusive).
*/
int RandInt(int min, int max);

/*
Parameters:
min - Minimum value to be randomly generated.
max - Maximum value to be randomly generated.
Returns:
Randomly generated value between min and max (inclusive).
*/
float RandFlo(float min, float max);

#endif
