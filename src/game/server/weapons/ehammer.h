#ifndef GAME_SERVER_WEAPONS_EHAMMER_H
#define GAME_SERVER_WEAPONS_EHAMMER_H

#include <game/server/weapon.h>

class CEHammer : public CWeapon
{
public:
	CEHammer(CCharacter *pOwnerChar);

	void Fire(vec2 Direction) override;
	int GetType() override { return WEAPON_HAMMER; }
};

#endif // GAME_SERVER_WEAPONS_HAMMER_H
