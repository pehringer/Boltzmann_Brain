#include "mutation.h"

// VERIFIED
void MutationPointChange(float *offspring, int genes, float min, float max) {
    int geneX = RandomRangeInt(0, genes - 1);
    // Change by adjusting current value.
    offspring[geneX] += RandomRangeFloat(min, max);
}

// VERIFIED
void MutationPointDeletion(float *offspring, int genes) {
    int geneX = RandomRangeInt(0, genes - 1);
    // Delete by writing zero value.
    offspring[geneX] = 0.0;
}

// VERIFIED
void MutationPointInsertion(float *offspring, int genes, float min, float max) {
    int geneX = RandomRangeInt(0, genes - 1);
    // Insert by writing new value.
    offspring[geneX] = RandomRangeFloat(min, max);
}

// VERIFIED
void MutationInversion(float *offspring, int genes, int min, int max) {
    int range = RandomRangeInt(min, max);
    int geneX = RandomRangeInt(0, genes - range);
    int geneY = geneX + range - 1;
    while(geneX <= geneY) {
	// Invert by swapping current values.
        float swap = offspring[geneX];
        offspring[geneX] = offspring[geneY];
        offspring[geneY] = swap;
	geneX++;
	geneY--;
    }
}

// VERIFIED
void MutationDeletion(float *offspring, int genes, int min, int max) {
    int range = RandomRangeInt(min, max);
    int geneX = RandomRangeInt(0, genes - range);
    int geneY = geneX + range - 1;
    while(geneX <= geneY) {
	// Delete by writing zero values.
        offspring[geneX] = 0.0;
        offspring[geneY] = 0.0;
        geneX++;
        geneY--;
    }
}

// VERIFIED
void MutationInsertion(float *offspring, int genes, int min, int max) {
    int range = RandomRangeInt(min, max);
    int geneX = RandomRangeInt(0, genes - range);
    int geneY = geneX + range - 1;
    int geneZ = RandomRangeInt(0, genes - range);
    // Iterate geneX to geneY.
    if(RandomFloat() < 0.5) {
        while(geneX <= geneY) {
            // Insert by copying and writing zero value.
            offspring[geneZ] = offspring[geneX];
            offspring[geneX] = 0.0;
	    geneX++;
	    geneZ++;
        }
    // Iterate geneY to geneX (inverted).
    } else {
        while(geneX <= geneY) {
            // Insert by copying and writing zero value.
            offspring[geneZ] = offspring[geneY];
            offspring[geneY] = 0.0;
	    geneY--;
	    geneZ++;
        }
    }
}

// VERIFIED
void MutationTranslocation(float *offspring, int genes, int min, int max) {
    int range = RandomRangeInt(min, max);
    int geneX = RandomRangeInt(0, genes - range);
    int geneY = geneX + range - 1;
    int geneZ = RandomRangeInt(0, genes - range);
    // Iterate geneX to geneY.
    if(RandomFloat() < 0.5) {
        while(geneX <= geneY) {
            // Translocate by swapping current values.
            float swap = offspring[geneX];
            offspring[geneX] = offspring[geneZ];
            offspring[geneZ] = swap;
	    geneX++;
	    geneZ++;
        }
    // Iterate geneY to geneX (inverted).
    } else {
        while(geneX <= geneY) {
            // Translocate by swapping current values.
            float swap = offspring[geneY];
            offspring[geneY] = offspring[geneZ];
            offspring[geneZ] = swap;
	    geneY--;
	    geneZ++;
        }
    }
}

// VERIFIED
void MutationDuplication(float *offspring, int genes, int min, int max) {
    int range = RandomRangeInt(min, max);
    int geneX = RandomRangeInt(0, genes - range);
    int geneY = geneX + range - 1;
    int geneZ = RandomRangeInt(0, genes - range);
    // Iterate geneX to geneY.
    if(RandomFloat() < 0.5) {
        while(geneX <= geneY) {
            // Duplicate by copying current value.
            offspring[geneZ] = offspring[geneX];
	    geneX++;
	    geneZ++;
        }
    // Iterate geneY to geneX (inverted).
    } else {
        while(geneX <= geneY) {
            // Duplicate by copying current value.
            offspring[geneZ] = offspring[geneY];
	    geneY--;
	    geneZ++;
        }
    }
}
