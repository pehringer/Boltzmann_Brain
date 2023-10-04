#include "crossover.h"

void CrossoverUniform(float *offspringGenome, float *maleGenome, float *femaleGenome, int genes) {
    int geneX = 0;
    while(geneX <= genes) {
	// Randomly select either male or female gene.
        if(RandomFloat() < 0.5) {
            offspringGenome[geneX] = maleGenome[geneX];
        } else {
            offspringGenome[geneX] = femaleGenome[geneX];
        }
        geneX++;
    }
}

void CrossoverAverage(float *offspringGenome, float *maleGenome, float *femaleGenome, int genes);
    int geneX = 0;
    while(geneX <= genes) {
	// Take average of male and female genes.
        offspringGenome[geneX] = maleGenome[geneX] + femaleGenome[geneX];
        offspringGenome[geneX] /= 2.0;
        geneX++;
    }
}

void CrossoverSinglePoint(float *offspringGenome, float *maleGenome, float *femaleGenome, int genes) {
    int geneX = 0;
    // Copy male genes from start to first point.
    int geneY = RandomRangeInt(0, genes - 1);
    while(geneX <= geneY) {
        offspringGenome[geneX] = maleGenome[geneX];
        geneX++
    }
    // Copy female genes from first point to end.
    geneY = genes - 1;
    while(geneX <= geneY) {
        offspringGenome[geneX] = femaleGenome[geneX];
        geneX++
    }
}

void CrossoverDoublePoint(float *offspringGenome, float *maleGenome, float *femaleGenome, int genes) {
    int geneX = 0;
    // Copy male genes from start to first point.
    int geneY = RandomRangeInt(0, genes / 2);
    while(geneX <= geneY) {
        offspringGenome[geneX] = maleGenome[geneX];
        geneX++
    }
    // Copy female genes from first point to second point.
    geneY = RandomRangeInt(genes / 2, genes - 1);
    while(geneX <= geneY) {
        offspringGenome[geneX] = femaleGenome[geneX];
        geneX++
    }
    // Copy male genes from second point to end.
    geneY = genes - 1;
    while(geneX <= geneY) {
        offspringGenome[geneX] = maleGenome[geneX];
        geneX++
    }
}

void CrossoverTriplePoint(float *offspringGenome, float *maleGenome, float *femaleGenome, int genes) {
    int geneX = 0;
    // Copy male genes from start to first point.
    int geneY = RandomRangeInt(0, genes / 3);
    while(geneX <= geneY) {
        offspringGenome[geneX] = maleGenome[geneX];
        geneX++
    }
    // Copy female genes from first point to second point.
    geneY = RandomRangeInt(genes / 3, genes / 3 * 2);
    while(geneX <= geneY) {
        offspringGenome[geneX] = femaleGenome[geneX];
        geneX++
    }
    // Copy male genes from second point to third point.
    geneY = RandomRangeInt(genes / 3 * 2, genes - 1);
    while(geneX <= geneY) {
        offspringGenome[geneX] = maleGenome[geneX];
        geneX++
    }
    // Copy feamle genes from third point to end.
    geneY = genes - 1;
    while(geneX <= geneY) {
        offspringGenome[geneX] = femaleGenome[geneX];
        geneX++
    }
}
