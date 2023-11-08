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
float Abs(float value);

/*
Parameters:
val - Value.
Returns:
Rectified linear unit of val.
*/
float ReLU(float value);

// Matrix & Vector Operations

/*
Parameters:
result - Vector that holds element for summation.
length - Length of result.
Returns:
Summation of result.
*/
float VecSum(float *result, int length);

/*
Parameters:
result - Vector that holds element-wise result.
length - Length of result.
operation - Operation to be performed on each element of result.
*/
void VecElemWise(float *result, int length, float (*operation)(float));
/*
Parameters:
result - Vector that holds vector-vector sum.
vector - Vector to be added to result.
length - Length of result and vector.
*/
void VecVecAdd(float *result, const float *vector, int length);

/*
Parameters:
result - Vector that holds vector-vector difference.
vector - Vector to be subtracted from result.
length - Length of result and vector.
*/
void VecVecSub(float *result, const float *vector, int length);

/*
Parameters:
result - Vector that holds matrix-vector product.
vector - Vector to be multiplied.
matrix - Matrix to be multiplied.
rows - Rows of matrix / length of result.
columns - Columns of matrix / length of vector.
*/
void MatVecMul(float *result, const float *matrix, const float *vector, int rows, int columns);


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
