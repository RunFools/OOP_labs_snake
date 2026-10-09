#pragma once

#include <random>


class Rand {
private:
    inline static std::mt19937 rng{ std::random_device{}() };

public:
    static int getRandInt(int min, int max);
};
