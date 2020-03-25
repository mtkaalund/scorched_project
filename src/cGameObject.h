#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <OneLoneCoder/olcPixelGameEngine.h>

// The base object for all objects in the game that have an actual, physical presence (location) and can be affected by physics
class cGameObject
{
	cGameObject(olc::vf2d location, float mass, bool affectedByWind, bool affectedByGravity);

public:
	// MOVEMENT AND LOCATION
	olc::vf2d location;
	olc::vf2d acceleration;
	olc::vf2d velocity;
	float fMaxSpeed;
	float fAngle;
	olc::vf2d angleVelocity;
	olc::vf2d angleAcceleration;

	// DISPLAY/RENDERING
	// Can't quite decide how to implement this. Probably the bounding box of the object, which is also used for collision checks, and then a texture to draw on that box?

	// PHYSICS
	bool bAffectedByWind; // The reason we have these two is because tanks are not affected by wind, only gravity (when the ground below them blows up)
	bool bAffectedByGravity;
	float fMass;
	bool bSettled; // Used for acting on when a physics object is at rest, and is no longer being affected by physics (wind, gravity, bouncing etc)

private:
	void applyForce(olc::vf2d force); // Scaled (multiplied) by the entity's mass, and added to cAcceleration
	olc::vf2d getAcceleration(olc::vf2d target);
	olc::vf2d getDrag(float coefficient); // "coefficient" being the strength of whatever force you are simulating (wind, liquid etc)

public:
	void applyGravity(float strength); // Gravity will be applied to the entity's velocity in the Y-axis only (and only down) 
	void applyWind(float strength); // Similar to gravity, just applied to the X-axies only (left or right)
    void applyFluidResistance(float strength);
	void checkCollision(cGameObject objects[]); // Might be done outside the objects instead of on them. Undecided how to handle yet
	void resolveCollision(); // Might be done outside the objects instead of on them. Undecided how to handle yet
	
	// TODO: Probably need implement functionality for stuff to bounce (like grenades that don't explode on impact)
	// Probably to be combined with collision checking. Bouncing should be as easy as just reversing the velocity vector on 
	// collision, scaled by some value, so that it loses power (acceleration) for each bounce
};

#endif