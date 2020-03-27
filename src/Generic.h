#ifndef GENERIC_H_
#define GENERIC_H_

#include <random>
#include <cmath>

// C++17 one can get PI with this code
template <typename T>
T const pi = std::acos(-T(1));

// Linear interpolation
// https://en.wikipedia.org/wiki/Linear_interpolation
template <typename T>
T lerp(T v0, T v1, T t)
{
    return (1 - t) * v0 + (t * v1);
}

// Taken from Perlin Noise Video https://youtu.be/6-0UaeJBumA
// Also from https://github.com/OneLoneCoder/videos/blob/master/worms/OneLoneCoder_Worms1.cpp
void PerlinNoise1D(int nCount, float *fSeed, int nOctaves, float fBias, float *fOutput)
{
    // Used 1D Perlin Noise
    for (int x = 0; x < nCount; x++)
    {
        float fNoise = 0.0f;
        float fScaleAcc = 0.0f;
        float fScale = 1.0f;

        for (int o = 0; o < nOctaves; o++)
        {
            int nPitch = nCount >> o;
            int nSample1 = (x / nPitch) * nPitch;
            int nSample2 = (nSample1 + nPitch) % nCount;
            float fBlend = (float)(x - nSample1) / (float)nPitch;
            float fSample = lerp<float>(fSeed[nSample1], fSeed[nSample2], fBlend);
            fScaleAcc += fScale;
            fNoise += fSample * fScale;
            fScale = fScale / fBias;
        }

        fOutput[x] = fNoise / fScaleAcc;
    }
}

// Simplex Noise (should be in the same family as Perlin noise)
// http://staffwww.itn.liu.se/~stegu/aqsis/aqsis-newnoise/simplexnoise1234.cpp
// lampda function of fastfloor
void SimplexNoise1D(int nCount, int *seed, float fFrequency, float *fOutput)
{
    float fFreq = 1.0f;
    

    // for (int x = 0; x < nCount; x++)
    // //for (int x = 0; x < 4; x++)
    // {

        
    // }


}

#if defined(_WIN64) || defined(__x86_64__)
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
#else
float randf(float a, float b)
{
    std::random_device rd;

    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(a, b);

    return dis(gen);
}

int randi(int a, int b)
{
    std::random_device rd;

    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(a, b);

    return dis(gen);
}
#endif

#endif