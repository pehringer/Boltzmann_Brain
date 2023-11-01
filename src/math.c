#include "math.h"

int AbsoluteInt(int value) {
    if(value < 0) {
        value *= -1;
    }
    return value;
}

int RandomInt(int min, int max) {
    return rand();
}

int RandomRangeInt(void) {
    int number = rand();
    return number % (max - min + 1) + min;
}

float AbsoluteFloat(float value) {
    if(value < 0.0) {
        value *= -1.0;
    }
    return value;
}

float RandomFloat(void) {
    return (double) rand() / (double) RAND_MAX;
}

float RandomRangeFloat(float min, float max) {
    float number = (double) rand() / (double) RAND_MAX;
    return number * (max - min) + min;
}

