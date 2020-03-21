#ifndef CPHYSICOBJECT_H_
#define CPHYSICOBJECT_H_

#include <OneLoneCoder/olcPixelGameEngine.h>

class cPhysicsObject
{
public:
    olc::vf2d location;
    olc::vf2d velocity;
    olc::vf2d acceleration;

    bool bIsDead;

    cPhysicsObject( olc::vf2d loc ) : location( loc ) 
    {
        bIsDead = false; // The object is not dead
    }

    virtual void Update( float fElapsedTime ) = 0;
    virtual void Display( olc::PixelGameEngine * engine ) = 0;
};

#endif