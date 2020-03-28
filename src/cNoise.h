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
            hash[i] = randi(0, length);
        }
        hashmask = length - 1;
    }

    float Smooth(float t)
    {
        return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
    }

    float SimplexValue1DValuePart( float fX, int iX)
    {
        float x = fX - iX;
        float f = 1.0f - x * x;
        float f2 = f * f;
        float f3 = f * f2;
        float h = hash[iX & hashmask];
        return f3 * h;
    }

    float Simplex1DPart( float fX, int iX)
    {
        float x = fX - iX;
        float f = 1.0f - x * x;
        float f2 = f * f;
        float f3 = f * f2;
        float h = hash[iX & hashmask];
        return f3 * h;
    }
public:
    Noise()
    {
        CreateHash(256);
    }

    Noise(int length)
    {
        CreateHash( length );
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
    float Perlin1D(int nX, float fFrequency)
    {
        float gradients1d[] = {-1, 1};
        int gradientsMask1d = 1;

        float fX = nX * fFrequency;
        int i0 = std::floor(fX);
        float t0 = fX - i0;
        float t1 = t0 - 1.0f;
        i0 &= hashmask;
        int i1 = i0 + 1;

        int g0 = gradients1d[ hash[i0] & gradientsMask1d ];
        int g1 = gradients1d[ hash[i1] & gradientsMask1d ];

        float v0 = g0 + t0;
        float v1 = g1 + t1;

        float t = Smooth(t0);
        return lerp<float>(v0, v1, t) * 0.25f + 0.5f;
    }

    // Noise Type Simplex
    float Simplex1D(int nX, float fFrequency )
    {
        float fX = nX * fFrequency;
        int ix = std::floor(fX);
        float sample = Simplex1DPart(fX, ix);
        sample += Simplex1DPart(fX, ix + 1);
        return sample * (1.0f / hashmask) - 0.6f;
    }
};

#endif