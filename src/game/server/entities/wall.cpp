/* (c) Shereef Marzouk. See "licence DDRace.txt" and the readme.txt in the root of the distribution for more information. */
#include "plasma.h"
#include <engine/config.h>
#include <engine/server.h>
#include <game/generated/protocol.h>
#include <game/server/gamecontext.h>
#include <game/server/player.h>
#include <game/server/teams.h>
#include <game/server/weapons.h>
#include "wall.h"

#include "character.h"

CWall::CWall(CGameWorld *pGameWorld, vec2 Pos, vec2 To,
	bool Explosive, int Owner, int Damage, vec2 ExploadingPoint) :
	CEntity(pGameWorld, CGameWorld::ENTTYPE_DDRACE)
{
	m_Pos = Pos;
	m_To = To;
	m_Explosive = Explosive;
	m_EvalTick = Server()->Tick();
	m_LifeTime = Server()->TickSpeed() * (5.0f / 60.0f);
	m_Owner = Owner;
	m_Damage = Damage;
	starttime = m_LifeTime;

	m_ExploadingPoint = ExploadingPoint;

	m_ID = Server()->SnapNewID();
	GameWorld()->InsertEntity(this);
}

bool CWall::HitCharacter(bool pointexp)
{
	CCharacter *Hit = GameWorld()->IntersectCharacter(m_Pos,
		m_To, 0.0f, GameServer()->GetPlayerChar(m_Owner));
	if(!Hit || !Hit->GetPlayer() || Hit->GetPlayer()->GetCID() == m_Owner)
		return false;
	if(m_Explosive)
		GameWorld()->CreateExplosion(pointexp ? m_Pos - m_ExploadingPoint : Hit->GetPos(), m_Owner, WEAPON_GRENADE, WEAPON_ID_GRENADE, m_Damage, false, -1LL, true);
	m_MarkedForDestroy = true;
	return true;
}


CWall::~CWall()
{
	Server()->SnapFreeID(m_ID);
}

void CWall::Reset()
{
	m_MarkedForDestroy = true;
}

void CWall::Tick()
{
	if(m_LifeTime == 0)
	{
		Reset();
		return;
	}
	m_LifeTime--;

	if (starttime - m_LifeTime > 3)
		HitCharacter(m_ExploadingPoint != vec2(0, 0));

	int Res = 0;
	Res = GameServer()->Collision()->IntersectNoLaser(m_Pos, m_To, 0,
		0);
//	if(Res)
	if(false)
	{
		if(m_Explosive)
			GameWorld()->CreateExplosion(
				m_Pos,
				m_Owner,
				WEAPON_GRENADE,
				WEAPON_ID_DDRACE,
				0,
				true,
				-1LL,
				true);
		Reset();
	}
}

void CWall::Snap(int SnappingClient, int OtherMode)
{
	if(OtherMode)
		return;

	int Tick = (Server()->Tick() % Server()->TickSpeed()) % 11;

	if(m_Layer == LAYER_SWITCH && m_Number > 0 && !GameServer()->Collision()->m_pSwitchers[m_Number].m_Status[GameWorld()->Team()] && (!Tick))
		return;

	CNetObj_Laser *pObj = static_cast<CNetObj_Laser *>(Server()->SnapNewItem(
		NETOBJTYPE_LASER, m_ID, sizeof(CNetObj_Laser)));

	if(!pObj)
		return;

	pObj->m_X = (int)m_Pos.x;
	pObj->m_Y = (int)m_Pos.y;
	pObj->m_FromX = (int)m_To.x;
	pObj->m_FromY = (int)m_To.y;
	pObj->m_StartTick = m_EvalTick;
}
