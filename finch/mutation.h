#ifndef MUTATION_H
#define MUTATION_H

#include "math.h"

void MutationPointChange(float *genome, int genes, float minAmount, float maxAmount);

void MutationPointDeletion(float *genome, int genes);

void MutationPointInsertion(float *genome, int genes, float minValue, float maxValue);

void MutationInversion(float *genome, int genes, int minGenes, int maxGenes);

void MutationDeletion(float *genome, int genes, int minGenes, int maxGenes);

void MutationInsertion(float *genome, int genes, int minGenes, int maxGenes);

void MutationDuplication(float *genome, int genes, int minGenes, int maxGenes);

void MutationTranslocation(float *genome, int genes, int minGenes, int maxGenes);

#endif
