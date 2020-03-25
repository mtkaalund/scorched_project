#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include <OneLoneCoder/olcPixelGameEngine.h>
#include <cGameObject.h>

// Projectiles are spawned by cWeapon when fired. Inherits the nDamage and fDamageRadius from the weapon that created it.
class cProjectile : cGameObject {

    cProjectile(unsigned int damage, float damageRadius, unsigned int activationTime=0);

public:
    unsigned int nRemainingActiveTime; // Set by activationTime and then counts down. On zero it explodes (call onDeath()). How to make this continous countdown work?
    bool bExplodeOnImpact; // Defaults to true, but gets auto-set by constructor to false is activationTime > 0
    unsigned int nDamage;
    float fDamageRadius;

    // If !bExplodeOnImpact then bounce on impact, otherwise call onDeath(). How should the bounce be handled, as it's effectively a physics action?
    // Should this be handled by collision detection and how?
    void onImpact();
    // Applies damage to objects (tanks->onGettingHit() and terrain) within fDamageRadius. Spawns debris for added visual flair (we can add this later)
    void onDeath();
};

#endif