#include "mutation.h"

void MutatePoint(struct Individual *i, float min, float max) {
    *(i->genome + RandomInt(0, i->genes - 1)) += RandomFloat(min, max);
}

void MutateDuplication(struct Individual *i, int min, int max) {
    int genes = RandomInt(min, max);
    float *geneX = i->genome + RandomInt(0, i->genes - genes * 2);
    float *geneY = geneX + genes;
    while(genes > 0) {
	*geneY = *geneX;
        geneX++;
        geneY++;
        genes--;
    }
}

void MutateInsertion(struct Individual *i, int min, int max) {
    int genes = RandomInt(min, max);
    float *geneX = i->genome + RandomInt(0, i->genes - genes);
    float *geneY = i->genome + RandomInt(0, i->genes - genes);
    while(genes > 0) {
        *geneY = *geneX;
        geneX++;
        geneY++;
        genes--;
    }
}

void MutateTranslocation(struct Individual *i, int min, int max) {
    int genes = RandomInt(min, max);
    float *geneX = i->genome + RandomInt(0, i->genes - genes);
    float *geneY = i->genome + RandomInt(0, i->genes - genes);
    while(genes > 0) {
	float swap = *geneY;
	*geneY = *geneX;
	geneX = swap;
        geneX++;
        geneY++;
        genes--;
    }
}

void MutateInversion(struct Individual *i, int min, int max) {
    int genes = RandomInt(min, max);
    float *geneX = i->genome + RandomInt(0, i->genes - genes);
    float *geneY = geneX + genes - 1;
    genes /= 2;
    while(genes > 0) {
	float swap = *geneY;
	*geneY = *geneX;
	geneX = swap;
        geneX++;
        geneY--;
        genes--;
    }
}
