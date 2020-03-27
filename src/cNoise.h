#ifndef CNOISE_H_
#define CNOISE_H_

#include <random>
#include <cmath>

#include "Generic.h"

// Inspireded by https://catlikecoding.com/unity/tutorials/noise/

class Noise
{
private:
    int hashmask;
    int *hash;

    void CreateHash(size_t length)
    {
        hash = new int[length];
        for (int i = 0; i < length; i++)
        {
            hash[i] = randi(0, 255);
        }
        hashmask = length - 1;
    }

    float Smooth( float t )
    {
        return t * t * t * (t * ( t * 6.0f - 15.0f) + 10.0f);
    }

public:
    Noise()
    {
        CreateHash(256);
    }

    Noise(int length)
    {
        CreateHash(length);
    }

    ~Noise()
    {
        delete[] hash;
    }

    // Noise type "value"
    float Value1D(int nX, float fFrequency)
    {
        float fX = nX * fFrequency;
        int i0 = std::floor(fX);
        float t = fX - i0;
        i0 &= hashmask;
        int i1 = i0 + 1;

        int h0 = hash[i0];
        int h1 = hash[i1];
        t = Smooth(t);
        return lerp<float>(h0, h1, t) * (1.0f / hashmask);
    }

    // Noise type "Perlin"
    float Perlin1D( int nX, float fFrequency)
    {
        float fX = nX * fFrequency;
        return 0.0f;
    }
};

#endif