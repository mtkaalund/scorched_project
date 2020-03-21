#ifndef CPHYSICOBJECT_H_
#define CPHYSICOBJECT_H_

#include <OneLoneCoder/olcPixelGameEngine.h>

class cPhysicsObject
{
public:
    olc::vf2d location;
    olc::vf2d velocity;
    olc::vf2d acceleration;

    cPhysicsObject( olc::vf2d loc ) : location( loc ) {}

};

#endif