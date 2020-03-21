#ifndef CPARTICLE_H_
#define CPARTICLE_H_

#include <OneLoneCoder/olcPixelGameEngine.h>

#include "cPhysicObject.h"

class cParticle : public cPhysicsObject
{
public:
    cParticle( olc::vf2d loc ) : cPhysicsObject(loc) {}

    void Update( float fElapsedTime ) override
    {
        velocity += acceleration;
        location += velocity;
    }

    void Display( olc::PixelGameEngine * engine ) override
    {       
        engine->DrawLine(location, location + olc::vf2d({0, 10}), olc::GREEN);
        engine->DrawCircle(location, 10, olc::RED);
    }
};

#endif