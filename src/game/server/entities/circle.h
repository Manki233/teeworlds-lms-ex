#ifndef GAME_SERVER_ENITIES_CIRCLE_H
#define GAME_SERVER_ENITIES_CIRCLE_H


#include <game/server/entity.h>

class CCircle : public CEntity
{
public:
	CCircle(CGameWorld *pGameWorld, vec2 Pos, vec2 force,
		bool Explosive, int Owner, int LifeTime, int Rad, bool Follow, int A = 10, int Damage = 0, vec2 *pCore = NULL);
	~CCircle();

	virtual void Reset();
	virtual void Tick();
	virtual void Snap(int SnappingClient, int OtherMode);

	int m_EvalTick;

	vec2 *m_pChar;
	
	int m_LifeTime;

	int m_Owner;

	int m_Damage;

	bool m_Follow;

	int m_Radius;

	int m_A;

	bool m_Explosive;

	vec2 m_Force;

	int m_ID;
};

#endif