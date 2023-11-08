#ifndef NETWORK_H
#define NETWORK_H

#include<stdlib.h>
#include<string.h>


/*
Members:
layers - Number of layers in network (including input and output layers).
sizes - First element contains input layers nueron count.
        Middle elements contain corresponding hidden layer nueron counts.
        Last element contains output layers nueron count.
params - Number of weights and biases in network.
*/
typedef struct NetConfig {
    int layers;
    int *sizes;
    int params;
} NetConfig;

typedef float* NetInputs;

typedef float* NetOutputs;

typedef float* NetParams;

NetConfig InitNetConfig(int layers, int *sizes);

void FreeNetConfig(NetConfig nc);

NetParams InitNetParams(NetConfig nc, float min, float max);

void FreeNetParams(NetParams np);


#endif
