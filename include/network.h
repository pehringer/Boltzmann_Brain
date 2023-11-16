#ifndef NETWORK_H
#define NETWORK_H

#include <stdlib.h>
#include <string.h>
#include "math.h"

struct Net{
    int   lays; // Length of wid (number of layers in network).
    int   pars; // Length of par.
    int   inps; // Lenght of inp.
    int   outs; // length of out.
    int   *wid; // Network layer widths (nuerons per layer).
    float *par; // Network parameters (weights/biases).
    float *inp; // Network layer inputs (intermediate calculations).
    float *out; // Network layer outputs (intermediate calculations).
};

/*
Parameters:
  - lays, number of layers in network.
  - wid, First element is input layer width.
    Middle elements are hidden layer widths.
    Last element is output layer widths.
Returns allocated network.
*/
struct Net NewNet(int lays, const int *wid);

/*
Parameters:
  - net, network to deallocate.
*/
void DelNet(struct Net net);

/*
Parameters:
  - net, network to initialize parameters.
  - min, minimum random parameter value.
  - max, maximum random parameter value.
*/
void IntNet(struct Net net, float min, float max);

/*
Parameters:
  - net, network to perform forward propagation on.
  - inp, inputs for forward propagation.
Returns network outputs from forward propagation.
*/
const float* ForPro(struct Net net, const float *inp);

/*
Parameters:
  - net, network to calculate output error.
  - inp, inputs for forward propagation.
Returns sum of the absolute difference of the networks last forward
  propagation outputs.
*/
float OutErr(struct Net net, const float *exp);


#endif
