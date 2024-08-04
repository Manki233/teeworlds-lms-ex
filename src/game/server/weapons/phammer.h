#ifndef GAME_SERVER_WEAPONS_PHAMMER_H
#define GAME_SERVER_WEAPONS_PHAMMER_H

#include <game/server/weapon.h>
#include <game/server/entities/wall.h>

class CPHammer : public CWeapon
{
public:
	CPHammer(CCharacter *pOwnerChar);

	void Fire(vec2 Direction) override;
	int GetType() override { return WEAPON_HAMMER; }

	int m_OwnerID;

	void OnTick () override;

	int mTmp = 0;
};

#endif // GAME_SERVER_WEAPONS_PHAMMER_H
