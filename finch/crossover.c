#include "crossover.h"

// VERIFIED
void CrossoverUniform(float *offspring, float *male, float *female, int genes) {
    int geneX = 0;
    while(geneX <= genes) {
	// Randomly select either male or female gene.
        if(RandomFloat() < 0.5) {
            offspring[geneX] = male[geneX];
        } else {
            offspring[geneX] = female[geneX];
        }
        geneX++;
    }
}

// VERIFIED
void CrossoverAverage(float *offspring, float *male, float *female, int genes) {
    int geneX = 0;
    while(geneX <= genes) {
	// Take average of male and female genes.
        offspring[geneX] = (male[geneX] + female[geneX]) / 2.0;
        geneX++;
    }
}

// VERIFIED
void CrossoverSinglePoint(float *offspring, float *male, float *female, int genes) {
    int geneX = 0;
    // Copy male genes from start to first point.
    int geneY = RandomRangeInt(0, genes);
    while(geneX < geneY) {
        offspring[geneX] = male[geneX];
        geneX++;
    }
    // Copy female genes from first point to end.
    geneY = genes;
    while(geneX < geneY) {
        offspring[geneX] = female[geneX];
        geneX++;
    }
}

// VERIFIED
void CrossoverDoublePoint(float *offspring, float *male, float *female, int genes) {
    int geneX = 0;
    // Copy male genes from start to first point.
    int geneY = RandomRangeInt(0, genes / 2);
    while(geneX < geneY) {
        offspring[geneX] = male[geneX];
        geneX++;
    }
    // Copy female genes from first point to second point.
    geneY = RandomRangeInt(genes / 2, genes);
    while(geneX < geneY) {
        offspring[geneX] = female[geneX];
        geneX++;
    }
    // Copy male genes from second point to end.
    geneY = genes;
    while(geneX < geneY) {
        offspring[geneX] = male[geneX];
        geneX++;
    }
}

// VERIFIED
void CrossoverTriplePoint(float *offspring, float *male, float *female, int genes) {
    int geneX = 0;
    // Copy male genes from start to first point.
    int geneY = RandomRangeInt(0, genes / 3);
    while(geneX < geneY) {
        offspring[geneX] = male[geneX];
        geneX++;
    }
    // Copy female genes from first point to second point.
    geneY = RandomRangeInt(genes / 3, genes / 3 * 2);
    while(geneX < geneY) {
        offspring[geneX] = female[geneX];
        geneX++;
    }
    // Copy male genes from second point to third point.
    geneY = RandomRangeInt(genes / 3 * 2, genes);
    while(geneX < geneY) {
        offspring[geneX] = male[geneX];
        geneX++;
    }
    // Copy feamle genes from third point to end.
    geneY = genes;
    while(geneX < geneY) {
        offspring[geneX] = female[geneX];
        geneX++;
    }
}
