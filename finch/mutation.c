#include "mutation.h"

void MutationPointChange(float *genome, int genes, float minAmount, float maxAmount) {
    int geneX = RandomRangeInt(0, genes - 1);
    // Change by adjusting current value.
    genome[geneX] += RandomRangeFloat(minAmount, maxAmount);
}

void MutationPointDeletion(float *genome, int genes) {
    int geneX = RandomRangeInt(0, genes - 1);
    // Delete by writing zero value.
    genome[geneX] = 0.0;
}

void MutationPointInsertion(float *genome, int genes, float minValue, float maxValue) {
    int geneX = RandomRangeInt(0, genes - 1);
    // Insert by writing new value.
    genome[geneX] = RandomRangeFloat(minValue, maxValue);
}

void MutationInversion(float *genome, int genes, int minGenes, int maxGenes) {
    int geneX = RandomRangeInt(0, genes - maxGenes);
    int geneY = geneX + RandomRangeInt(minGenes - 1, maxGenes - 1);
    while(geneX <= geneY) {
	// Invert by swapping current values.
        float swap = genome[geneX];
        genome[geneX] = genome[geneY];
        genome[geneY] = swap;
	geneX++;
	geneY--;
    }
}

void MutationDeletion(float *genome, int genes, int minGenes, int maxGenes) {
    int geneX = RandomRangeInt(0, genes - maxGenes);
    int geneY = geneX + RandomRangeInt(minGenes - 1, maxGenes - 1);
    while(geneX <= geneY) {
	// Delete by writing zero values.
        genome[geneX] = 0.0;
        genome[geneY] = 0.0;
        geneX++;
        geneY--;
    }
}

void MutationInsertion(float *genome, int genes, int minGenes, int maxGenes) {
    int geneX = RandomRangeInt(0, genes - maxGenes);
    int geneY = geneX + RandomRangeInt(minGenes - 1, maxGenes - 1);
    int geneZ = RandomRangeInt(0, genes - maxGenes);
    // Iterate geneX to geneY.
    if(RandomFloat() < 0.5) {
        while(geneX <= geneY) {
            // Insert by copying and writing zero value.
            genome[geneZ] = genome[geneX];
            genome[geneX] = 0.0;
	    geneX++;
	    geneZ++;
        }
    // Iterate geneY to geneX (inverted).
    } else {
        while(geneX <= geneY) {
            // Insert by copying and writing zero value.
            genome[geneZ] = genome[geneY];
            genome[geneY] = 0.0;
	    geneY--;
	    geneZ++;
        }
    }
}

void MutationTranslocation(float *genome, int genes, int minGenes, int maxGenes) {
    int geneX = RandomRangeInt(0, genes - maxGenes);
    int geneY = geneX + RandomRangeInt(minGenes - 1, maxGenes - 1);
    int geneZ = RandomRangeInt(0, genes - maxGenes);
    // Iterate geneX to geneY.
    if(RandomFloat() < 0.5) {
        while(geneX <= geneY) {
            // Translocate by swapping current values.
            float swap = genome[geneX];
            genome[geneX] = genome[geneZ];
            genome[geneZ] = swap;
	    geneX++;
	    geneZ++;
        }
    // Iterate geneY to geneX (inverted).
    } else {
        while(geneX <= geneY) {
            // Translocate by swapping current values.
            float swap = genome[geneY];
            genome[geneY] = genome[geneZ];
            genome[geneZ] = swap;
	    geneY--;
	    geneZ++;
        }
    }
}

void MutationDuplication(float *genome, int genes, int minGenes, int maxGenes) {
    int geneX = RandomRangeInt(0, genes - maxGenes);
    int geneY = geneX + RandomRangeInt(minGenes - 1, maxGenes - 1);
    int geneZ = RandomRangeInt(0, genes - maxGenes);
    // Iterate geneX to geneY.
    if(RandomFloat() < 0.5) {
        while(geneX <= geneY) {
            // Duplicate by copying current value.
            genome[geneZ] = genome[geneX];
	    geneX++;
	    geneZ++;
        }
    // Iterate geneY to geneX (inverted).
    } else {
        while(geneX <= geneY) {
            // Duplicate by copying current value.
            genome[geneZ] = genome[geneY];
	    geneY--;
	    geneZ++;
        }
    }
}
