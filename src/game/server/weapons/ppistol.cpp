#include "ppistol.h"
#include <game/generated/server_data.h>
#include <game/server/entities/circle.h>

CPPistol::CPPistol(CCharacter *pOwnerChar) :
	CWeapon(pOwnerChar)
{
	m_MaxAmmo = 3;
	m_AmmoRegenTime = 2000;
	m_FireDelay = 100;
}

bool CPPistol::BulletCollide(CProjectile *pProj, vec2 Pos, CCharacter *pHit, bool EndOfLife)
{
	return false;
}

void CPPistol::Fire(vec2 Direction)
{
	int ClientID = Character()->GetPlayer()->GetCID();

	vec2 ProjStartPos = Pos() + Direction * GetProximityRadius() * 0.75f;

//	CCircle::CCircle(CGameWorld *pGameWorld, vec2 Pos, vec2 force,
//		bool Explosive, int Owner, int LifeTime, int Rad, bool Follow, int A, int Damage, vec2 *pCore)

	new CCircle(GameWorld(), ProjStartPos, vec2(Direction. x * 25, Direction. y * 25), true, ClientID, 100000, 64, false, 12, 0, NULL);
	
	GameWorld()->CreateSound(Character()->m_Pos, SOUND_GUN_FIRE);
}