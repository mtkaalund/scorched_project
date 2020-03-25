#include <OneLoneCoder/olcPixelGameEngine.h>

class cGameObject
{
	cGameObject(olc::vf2d location, float mass, float maxSpeed, bool affectedByWind, bool affectedByGravity)
    {
        this->location = location;
        fMass = mass;
        fMaxSpeed = maxSpeed;
        bAffectedByWind = affectedByWind;
        bAffectedByGravity = affectedByGravity;
    };

public:
	// MOVEMENT AND LOCATION
	olc::vf2d location;
	float fMaxSpeed;
	float fAngle = 0.0f;
	olc::vf2d acceleration = olc::vf2d(0.0f, 0.0f);
	olc::vf2d velocity = olc::vf2d(0.0f, 0.0f);
	olc::vf2d angleVelocity = olc::vf2d(0.0f, 0.0f);
	olc::vf2d angleAcceleration = olc::vf2d(0.0f, 0.0f);

	// DISPLAY/RENDERING

	// PHYSICS
	bool bAffectedByWind;
	bool bAffectedByGravity;
	float fMass;
	bool bSettled = true;

private:
	void applyForce(olc::vf2d force)
    {
        olc::vf2d forceAfterMass = force / fMass;
		this->acceleration + forceAfterMass;
    }

	olc::vf2d getAcceleration(olc::vf2d target)
    {
        olc::vf2d direction = target - this->location; // Calculate a vector that points from this object (origin) to the target location
		direction = direction.norm(); // Normalize that vector (reducing its length to 1 "unit")
		direction = direction * (0.5 * this->fMass); // Scale that vector to an appropriate value, influenced by mass (the greater the mass, the slower the acceleration)

		return direction;
    }

	olc::vf2d getDrag(float coefficient)
    {
        float speed = this->velocity.mag();
		float dragMagnitude = coefficient * speed * speed;
        // Copy the velocity, reverse then normalize it, and finally multiply by the magnitude of the drag
		return olc::vf2d(this->velocity.x * -1, this->velocity.y * -1).norm() * dragMagnitude;
    }

public:
	void applyGravity(float strength)
    {
        this->applyForce(olc::vf2d(0, strength));
    }

	void applyWind(float strength)
    {
        this->applyForce(olc::vf2d(strength, 0));
    }

    void applyFluidResistance(float strength)
    {
        this->applyForce(this->getDrag(strength));
    }

	void checkCollision(cGameObject objects[]) {};
	void resolveCollision() {};
};