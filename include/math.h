#ifndef MATH_H
#define MATH_H

#include <stdlib.h>

/*
Parameters:
  - rows, number of rows in mat.
  - cols, number of cols in mat.
  - mat, matrix to perform summation on.
Returns the summation of mat elements.
*/
float MatSum(int rows, int cols, const float *mat);

/*
Parameters:
  - rows, number of rows in mat and res.
  - cols, number of cols in mat ans res.
  - mat, matrix to perform element wise absolute value.
  - res, matrix to store element wise results.
*/
void MatAbs(int rows, int cols, const float *mat, float *res);

/*
Parameters:
  - rows, number of rows in mat and res.
  - cols, number of cols in mat and res.
  - mat, matrix to perform element wise rectified linear unit.
  - res, matrix to store element wise results.
*/
void MatRLU(int rows, int cols, const float *mat, float *res);


/*
Parameters:
  - rows, number of rows in matA, matB, and res.
  - cols, number of cols in matA, matB, and res.
  - matA, matrix to perform element wise addition.
  - matB, matrix to perform element wise addition.
  - res, matrix to store element wise results.
*/
void MatAdd(int rows, int cols, const float *matA, const float *matB, float *res);

/*
Parameters:
  - rows, number of rows in matA, matB, and res.
  - cols, number of cols in matA, matB, and res.
  - matA, matrix to perform element wise subtraction.
  - matB, matrix to perform element wise subtraction.
  - res, matrix to store element wise results.
*/
void MatSub(int rows, int cols, const float *matA, const float *matB, float *res);

/*
Parameters:
  - rows, number of rows in mat, length of res.
  - cols, number of cols in mat, length of vec./
  - mat, matrix to perform matrix-vector multiplication.
  - vec, vector to perform matrix vector multiplication.
  - res, vector to store results.
*/
void MatMul(int rows, int cols, const float *mat, const float *vec, float *res);

#endif
