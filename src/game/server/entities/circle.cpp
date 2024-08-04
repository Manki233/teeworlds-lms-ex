#include "wall.h"
#include <engine/config.h>
#include <engine/server.h>
#include <game/generated/protocol.h>
#include <game/server/gamecontext.h>
#include <game/server/player.h>

#include "circle.h"

CCircle::CCircle(CGameWorld *pGameWorld, vec2 Pos, vec2 force,
	bool Explosive, int Owner, int LifeTime, int Rad, bool Follow, int A, int Damage, vec2 *pCore) :
	CEntity(pGameWorld, CGameWorld::ENTTYPE_DDRACE)
{
	m_LifeTime = LifeTime;
	m_Pos = Pos;
	m_Force = force;
	m_Explosive = Explosive;
	m_EvalTick = Server()->Tick();
	m_LifeTime = Server()->TickSpeed() * LifeTime / 60.0f;
	m_Owner = Owner;
	m_Damage = Damage;
	m_Radius = Rad;
	m_A = A;
	m_Follow = Follow;
	m_pChar = pCore;

	m_ID = Server()->SnapNewID();
	GameWorld()->InsertEntity(this);
}

void CCircle::Reset()
{
	m_MarkedForDestroy = true;
}


CCircle::~CCircle()
{
	Server()->SnapFreeID(m_ID);
}

void CCircle::Tick()
{
	if(m_LifeTime == 0)
	{
		Reset();
		return;
	}
	m_LifeTime--;
	
	m_Pos += m_Force;

	int Res = 0;
	Res = GameServer()->Collision()->IntersectNoLaser(m_Pos, m_Pos + m_Force, 0,
		0);

	if (m_Follow)
		m_Pos = *m_pChar;
	
	if(Res)
	{
		if(m_Explosive)
			GameWorld()->CreateExplosion(
				m_Pos,
				-1,
				WEAPON_GRENADE,
				-1,
				0,
				true,
				-1LL);
		Reset();
	}
}

#define MPI 3.1415926

void CCircle::Snap(int SnappingClient, int OtherMode)
{	
	int cnt = m_A;
	int alpha = 360 / cnt;
	
	for (int i = 0 ; i < cnt ; i ++)
	{
		float nowangle = i * alpha * MPI / 180.0f;
		float nextangle = (i + 1) * alpha * MPI / 180.0f;

		new CWall (
			GameWorld(),
			m_Pos + vec2(cos(nowangle) * m_Radius, sin(nowangle) * m_Radius), 
			m_Pos + vec2(cos(nextangle) * m_Radius, sin(nextangle) * m_Radius),
			m_Explosive,
			m_Owner,
			m_Damage,
			m_Force
		);
	}
}