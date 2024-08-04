#ifndef GAME_SERVER_WEAPONS_MGRENATE_H
#define GAME_SERVER_WEAPONS_MGRENATE_H

#include <game/server/weapon.h>

class CMGrenade : public CWeapon
{
public:
	CMGrenade(CCharacter *pOwnerChar);

	void Fire(vec2 Direction) override;
	int GetType() override { return WEAPON_GRENADE; }

	// callback
	static bool GrenadeCollide(class CProjectile *pProj, vec2 Pos, CCharacter *pHit, bool EndOfLife);
};

#endif // GAME_SERVER_WEAPONS_MGRENATE_H
