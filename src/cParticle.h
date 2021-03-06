#ifndef CPARTICLE_H_
#define CPARTICLE_H_

#include <OneLoneCoder/olcPixelGameEngine.h>

#include "cPhysicObject.h"
#include "Generic.h"

class cParticle : public cPhysicsObject
{
public:
    float fRadius;

    cParticle( olc::vf2d loc ) : cPhysicsObject(loc) {
        fRadius = randf(4.0f, 10.0f);
    }

    void Update( float fElapsedTime ) override
    {
        velocity += acceleration;
        location += velocity;
    }

    void Display( olc::PixelGameEngine * engine, olc::vf2d fOffset ) override
    {       
        engine->DrawLine(location - fOffset, location - fOffset + olc::vf2d({0, 10}), olc::GREEN);
        engine->DrawCircle(location - fOffset, 10, olc::RED);
    }
};

#endif