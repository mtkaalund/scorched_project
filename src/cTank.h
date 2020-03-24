#pragma once

#include <OneLoneCoder/olcPixelGameEngine.h>
#include <cGameObject.h>
#include <cWeapon.h>
#include <cProjectile.h>

class cTank : cGameObject
{
    cTank(std::string name, olc::vf2d location, std::list<cWeapon> weapons, int health=100);

private:
    std::list<cWeapon> weapons;
    unsigned int currentWeaponIndex;

public:
    std::string sName; // Player or AI name
    float fTurretAngle; // Angle of the turrent in radians. Default to something sensible (90 degrees or something)
    float fFiringPower; // The power (acceleration) to apply to the projectile of the chosen weapon when fired. Should be changeable by user via keyboard.
    int nHealth; // 0 or below means dead. Below zero values allows up to calculate overkill (might be fun or useful). Set/calculated in onGettingHit().

    cWeapon getCurrentWeapon(); // Returns weapons[currentWeaponIndex];
    void cycleNextWeapon(); // Increments currentWeaponIndex. If it's bigger than "weapons" size, then wrap around to 0.
    void cyclePreviousWeapon(); // Same as above, just in reverse.
    void fireWeapon(); // Get current weapon and call onFired() on it
    void onGettingHit(unsigned int damage); // Apply damage to self based on projectile. Maybe used for other things? Maybe we could scale damage based on the distance from the center of the impact of the projectile?
    void onDeath(); // Remove from game? Explode? Keep in game but mark as dead/inactive?
    void addWeapon(cWeapon weapon); // Maybe you can get new weapons during a round? Supply drops? Something else?
};