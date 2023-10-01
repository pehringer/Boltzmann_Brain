#include "mutation.h"

void PointChange(struct Individual *i, float minAmount, float maxAmount) {
    int geneX = RandomRangeInt(0, i->genes - 1);
    // Change by adjusting current value.
    i->genome[geneX] += RandomRangeFloat(minAmount, maxAmount);
}

void PointDeletion(struct Individual *i) {
    int geneX = RandomRangeInt(0, i->genes - 1);
    // Delete by writing zero value.
    i->genome[geneX] = 0.0;
}

void PointInsertion(struct Individual *i, float minValue, float maxValue) {
    int geneX = RandomRangeInt(0, i->genes - 1);
    // Insert by writing new value.
    i->genome[geneX] = RandomRangeFloat(minValue, maxValue);
}

void SegmentInversion(struct Individual *i, int minGenes, int maxGenes) {
    int geneX = RandomRangeInt(0, i->genes - maxGenes);
    int geneY = geneX + RandomRangeInt(minGenes, maxGenes - 1);
    while(geneX <= geneY) {
	// Invert by swapping current values.
        float swap = i->genome[geneX];
        i->genome[geneX] = i->genome[geneY];
        i->genome[geneY] = swap;
	geneX++;
	geneY--;
    }
}

void SegmentDeletion(struct Individual *i, int minGenes, int maxGenes) {
    int geneX = RandomRnageInt(0, i->genes - maxGenes);
    int geneY = geneX + RandomRangeInt(minGenes, maxGenes - 1);
    while(geneX <= geneY) {
	// Delete by writing zero values.
        i->genome[geneX] = 0.0;
        i->genome[geneY] = 0.0;
        geneX++;
        geneY--;
    }
}

void SegmentInsertion(struct Individual *i, int minGenes, int maxGenes) {
    int geneX = RandomRangeInt(0, i->genes - maxGenes);
    int geneY = geneX + RandomRangeInt(minGenes, maxGenes - 1);
    int geneZ = RandomRangeInt(0, i->genes - maxGenes);
    // Iterate geneX to geneY.
    if(RandomFloat() < 0.5) {
        while(geneX <= geneY) {
            // Insert by copying and writing zero value.
            i->genome[geneZ] = i->genome[geneX];
            i->genome[geneX] = 0.0;
	    geneX++;
	    geneZ++;
        }
    // Iterate geneY to geneX (inverted).
    } else {
        while(geneX <= geneY) {
            // Insert by copying and writing zero value.
            i->genome[geneZ] = i->genome[geneY];
            i->genome[geneY] = 0.0;
	    geneY--;
	    geneZ++;
        }
    }
}

void SegmentDuplication(struct Individual *i int minGenes, int maxGenes) {
    int geneX = RandomRangeInt(0, i->genes - maxGenes);
    int geneY = geneX + RandomRangeInt(minGenes, maxGenes - 1);
    int geneZ = RandomRangeInt(0, i->genes - maxGenes);
    // Iterate geneX to geneY.
    if(RandomFloat() < 0.5) {
        while(geneX <= geneY) {
            // Duplicate by copying current value.
            i->genome[geneZ] = i->genome[geneX];
	    geneX++;
	    geneZ++;
        }
    // Iterate geneY to geneX (inverted).
    } else {
        while(geneX <= geneY) {
            // Duplicate by copying current value.
            i->genome[geneZ] = i->genome[geneY];
	    geneY--;
	    geneZ++;
        }
    }
}

void SegmentTranslocation(struct Individual *i int minGenes, int maxGenes) {
    int geneX = RandomRangeInt(0, i->genes - maxGenes);
    int geneY = geneX + RandomRangeInt(minGenes, maxGenes - 1);
    int geneZ = RandomRangeInt(0, i->genes - maxGenes);
    // Iterate geneX to geneY.
    if(RandomFloat() < 0.5) {
        while(geneX <= geneY) {
            // Translocate by swapping current values.
            i->genome[geneZ] = i->genome[geneX];
	    geneX++;
	    geneZ++;
        }
    // Iterate geneY to geneX (inverted).
    } else {
        while(geneX <= geneY) {
            // Translocate by swapping current values.
            i->genome[geneZ] = i->genome[geneY];
	    geneY--;
	    geneZ++;
        }
    }
}
