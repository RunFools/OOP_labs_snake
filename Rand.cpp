#include "Rand.h"

int Rand::getRandInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}