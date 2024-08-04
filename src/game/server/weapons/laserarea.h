#ifndef GAME_SERVER_WEAPONS_LASERGUNAREA_H
#define GAME_SERVER_WEAPONS_LASERGUNAREA_H

#include <game/server/weapon.h>

class CLaserGunArea : public CWeapon
{
public:
	CLaserGunArea(CCharacter *pOwnerChar);

	void Fire(vec2 Direction) override;
	int GetType() override { return WEAPON_LASER; }

	// callback
	// static bool LaserHit(class CLaser *pLaser, vec2 HitPoint, CCharacter *pHit, bool OutOfEnergy);
};

#endif // GAME_SERVER_WEAPONS_LASERGUNAREA_H
