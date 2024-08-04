#ifndef GAME_SERVER_WEAPONS_HSHOTGUN_H
#define GAME_SERVER_WEAPONS_HSHOTGUN_H

#include <game/server/weapon.h>

class CHShotgun : public CWeapon
{
public:
	CHShotgun(CCharacter *pOwnerChar);

	void Fire(vec2 Direction) override;
	int GetType() override { return WEAPON_SHOTGUN; }

	// callback
	static bool BulletCollide(class CProjectile *pProj, vec2 Pos, CCharacter *pHit, bool EndOfLife);
};

#endif // GAME_SERVER_WEAPONS_HSHOTGUN_H
