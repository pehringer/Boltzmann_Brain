#ifndef CROSSOVER_H
#define CROSSOVER_H

#include "math.h"

void CrossoverUniform(float *offspring, float *male, float *female, int genes);

void CrossoverAverage(float *offspring, float *male, float *female, int genes);

void CrossoverSinglePoint(float *offspring, float *male, float *female, int genes);

void CrossoverDoublePoint(float *offspring, float *male, float *female, int genes);

void CrossoverTriplePoint(float *offspring, float *male, float *female, int genes);

#endif
