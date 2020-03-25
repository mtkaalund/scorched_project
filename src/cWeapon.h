#ifndef WEAPON_H_
#define WEAPON_H_

#include <OneLoneCoder/olcPixelGameEngine.h>
#include <cGameObject.h>

// Does not extend cGameObject because weapons don't physically exist in the gameworld. They are stats and info about the weapon and how it behaves.
// Each weapon (like a Grenade or Missile) is an instance of this class.
class cWeapon
{
    cWeapon(std::string name, unsigned int damage, float damageRadius, unsigned int ammo, unsigned int projectiles=1, unsigned int activationTime=0);

public:
    unsigned int nActivationTime; // If non-zero then this is a countdown in seconds before the projectile explodes (for grenades).
    unsigned int nDamage;// The damage to apply to objects (tanks only really...) within the fDamageRadius. Terrain is always destroyed by damage, no matter how small the damage is I guess.
    float fDamageRadius; // Most things are explosive (in a circular pattern) but I guess you could make direct damage weapons like a minigun by setting the radius to 0 or 1?
    std::string sName; // For display purposes
    unsigned int nAmmo; // How many shots left. Have to decide if nProjectiles > 1 do we reduce ammo by nProjectiles? Or just 1 ammo per shot, regardless of nProjectiles?
    unsigned int nProjectiles; // Maybe some weapons spit out multiple projectiles? Like firing a group of grenades/bombs/missiles?

    // Called when weapon is fired. By default it does this:
    // - spawns X projectiles based on nProjectiles in front of the turret
    // - spawning should be delayed, or projectiles will overlap and likely explode each other
    // - apply acceleration in the direction of the tank's turret angle based on tanks firing power
    // - gravity and wind takes care of the rest
    void onFired();
};

#endif