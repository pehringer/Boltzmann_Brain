#include "math.h"

int AbsoluteInt(int value) {
    // Make positive.
    if(value < 0) {
        value *= -1;
    }
    return value;
}

float AbsoluteFloat(float value) {
    // Make positive.
    if(value < 0.0) {
        value *= -1.0;
    }
    return value;
}

int RandomRangeInt(int min, int max) {
    // Get number between 0 and MAX_INT.
    int number = rand();
    // Apply min and max range to number.
    return number % (max - min + 1) + min;
}

float RandomRangeFloat(float min, float max) {
    // Get number between 0.0 and 1.0.
    float number = (double) rand() / (double) RAND_MAX;
    // Apply min and max range to number.
    return number * (max - min) + min;
}

float RandomFloat(void) {
    // Get number betwwen 0.0 and 1.0.
    return (double) rand() / (double) RAND_MAX;
}
