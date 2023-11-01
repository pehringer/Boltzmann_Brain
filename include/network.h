#ifndef NETWORK_H
#define NETWORK_H

#include<stdlib.h>
#include<string.h>

typedef float* NetParams;

typedef struct NetConfig {
    int layers;
    int *sizes;
    int params;
} NetConfig;

NetConfig InitNetConfig(int layers, int *sizes);

void FreeNetConfig(NetConfig nc);

NetParams InitNetParams(NetConfig nc, float min, float max);

void FreeNetParams(NetParams np);


#endif
