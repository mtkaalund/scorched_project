#ifndef GENERIC_H_
#define GENERIC_H_

#include <random>
#include <cmath>

// C++17 one can get PI with this code
template <typename T>
T const pi = std::acos(-T(1));

// C++17 float random generator
float randf(float a, float b)
{
    std::random_device rd;

    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<float> dis(a, b);

    return dis(gen);
}

int randi(int a, int b)
{
    std::random_device rd;

    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> dis(a, b);

    return dis(gen);
}

#endif