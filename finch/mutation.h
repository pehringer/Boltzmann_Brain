#ifndef MUTATION_H
#define MUTATION_H

#include "math.h"

void MutationPointChange(float *genome, int genes, float min, float max);

void MutationPointDeletion(float *genome, int genes);

void MutationPointInsertion(float *genome, int genes, float min, float max);

void MutationInversion(float *genome, int genes, int min, int max);

void MutationDeletion(float *genome, int genes, int min, int max);

void MutationInsertion(float *genome, int genes, int min, int max);

void MutationDuplication(float *genome, int genes, int min, int max);

void MutationTranslocation(float *genome, int genes, int min, int max);

#endif
