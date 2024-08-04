/* (c) Shereef Marzouk. See "licence DDRace.txt" and the readme.txt in the root of the distribution for more information. */
#ifndef GAME_SERVER_ENTITIES_WALL_H
#define GAME_SERVER_ENTITIES_WALL_H

#include <game/server/entity.h>

class CWall : public CEntity
{
	vec2 m_To;
	int m_EvalTick;
	int m_LifeTime;

	int m_Owner;

	int m_Freeze;

	int m_Damage;

	int starttime;

	bool m_Explosive;
	int m_ID;
	bool HitCharacter(bool pointexp = false);

	vec2 m_ExploadingPoint;

public:
	CWall(CGameWorld *pGameWorld, vec2 Pos, vec2 To,
		bool Explosive, int Owner, int Damage = 0, vec2 ExploadingPoint = vec2(0, 0));
	~CWall();

	virtual void Reset();
	virtual void Tick();
	virtual void Snap(int SnappingClient, int OtherMode);
};

#endif // GAME_SERVER_ENTITIES_WALL_H
