#ifndef GAME_SERVER_WEAPONS_PPISTOL_H
#define GAME_SERVER_WEAPONS_PPISTOL_H

#include <game/server/weapon.h>

class CPPistol : public CWeapon
{
public:
	CPPistol(CCharacter *pOwnerChar);

	void Fire(vec2 Direction) override;
	int GetType() override { return WEAPON_GUN; }

	// callback
	static bool BulletCollide(class CProjectile *pProj, vec2 Pos, CCharacter *pHit, bool EndOfLife);
	static bool BulletCollideTeamDamage(class CProjectile *pProj, vec2 Pos, CCharacter *pHit, bool EndOfLife);
};

#endif // GAME_SERVER_WEAPONS_PPISTOL_H
