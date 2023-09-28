#ifndef MUTATION_H
#define MUTATION_H

#include "math.c"

struct Individual {
    double fitness;
    int genes;
    float *genome;
}

void MutatePoint(struct Individual *i, float minimum, float maximum);

void MutateDuplication(struct Individual *i, int min, int max);

void MutateInsertion(struct Individual *i, int min, int max);

void MutateTranslocation(struct Individual *i, int min, int max);

void MutateInversion(struct Individual *i, int min, int max);

#endif
