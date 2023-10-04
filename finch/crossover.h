#ifndef CROSSOVER_H
#define CROSSOVER_H

#include "math.h"

void CrossoverUniform(float *offspringGenome, float *maleGenome, float *femaleGenome, int genes);

void CrossoverAverage(float *offspringGenome, float *maleGenome, float *femaleGenome, int genes);

void CrossoverSinglePoint(float *offspringGenome, float *maleGenome, float *femaleGenome, int genes);

void CrossoverDoublePoint(float *offspringGenome, float *maleGenome, float *femaleGenome, int genes);

void CrossoverTriplePoint(float *offspringGenome, float *maleGenome, float *femaleGenome, int genes);

#endif
