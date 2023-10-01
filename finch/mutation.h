#ifndef MUTATION_H
#define MUTATION_H

#include "math.c"

struct Individual {
    double fitness;
    int genes;
    float *genome;
};

void PointChange(struct Individual *i, float minAmount, float maxAmount);

void PointDeletion(struct Individual *i);

void PointInsertion(struct Individual *i, float minValue, float maxValue);

void SegmentInversion(struct Individual *i, int minGenes, int maxGenes);

void SegmentDeletion(struct Individual *i, int minGenes, int maxGenes);

void SegmentInsertion(struct Individual *i, int minGenes, int maxGenes);

void SegmentDuplication(struct Individual *i, int minGenes, int maxGenes);

void SegmentTranslocation(struct Individual *i, int minGenes, int maxGenes);

#endif
