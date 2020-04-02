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
        olc::vf2d fLineEnd = {
            2 * fRadius * cosf( fAngle * pi<float>/360.0f) ,
            2 * fRadius * sinf( fAngle * pi<float>/360.0f)
        };

        fLineEnd += location;

        engine->DrawLine(location - fOffset, fLineEnd , olc::DARK_RED);
        engine->DrawCircle(location - fOffset, (int)fRadius, olc::RED);
    }
};

#endif