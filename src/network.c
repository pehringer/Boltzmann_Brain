#include "network.h"


NetConfig InitNetConfig(int layers, int *sizes) {
    NetConfig nc;
    nc.layers = layers;
    nc.sizes = malloc(layers * sizeof(int));
    memcpy(nc.sizes, sizes, layers * sizeof(int));
    nc.params = 0;
    for(int i = 1; i < layers; i++) {
        nc.params += sizes[i] * sizes[i-1] + sizes[i];
    }
    return nc;
}

void FreeNetConfig(NetConfig nc) {
    free(nc.sizes);
}

NetParams InitNetParams(NetConfig nc, float min, float max) {
    NetParams np = malloc(nc.params * sizeof(float));
    for(int i = 0; i < nc.params; i++) {
        np[i] = RandomRangeFloat(min, max);
    }
    return np;
}

void FreeNetParams(NetParams np) {
    free(np);
}
