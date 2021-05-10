#include "pistol.h"
#include <game/generated/server_data.h>
#include <game/server/entities/projectile.h>

CPistol::CPistol(CCharacter *pOwnerChar) :
	CWeapon(pOwnerChar)
{
	m_MaxAmmo = g_pData->m_Weapons.m_aId[WEAPON_GUN].m_Maxammo;
	m_AmmoRegenTime = g_pData->m_Weapons.m_aId[WEAPON_GUN].m_Ammoregentime;
	m_FireDelay = Character()->CurrentTuning()->m_GunFireDelay;
}

bool CPistol::BulletCollide(CProjectile *pProj, vec2 Pos, CCharacter *pHit, bool EndOfLife)
{
	if(pHit)
		pHit->TakeDamage(vec2(0, 0), g_pData->m_Weapons.m_Gun.m_pBase->m_Damage, pProj->GetOwner(), WEAPON_GUN);

	return true;
}

void CPistol::Fire(vec2 Direction)
{
	int ClientID = Character()->GetPlayer()->GetCID();
	int Lifetime = Character()->CurrentTuning()->m_GunLifetime * Server()->TickSpeed();

	vec2 ProjStartPos = Pos() + Direction * GetProximityRadius() * 0.75f;

	CProjectile *pProj = new CProjectile(
		GameWorld(),
		WEAPON_GUN, //Type
		ClientID, //Owner
		ProjStartPos, //Pos
		Direction, //Dir
		6.0f,
		Lifetime, //Span
		BulletCollide);

	// pack the Projectile and send it to the client Directly
	CNetObj_Projectile p;
	pProj->FillInfo(&p);

	CMsgPacker Msg(NETMSGTYPE_SV_EXTRAPROJECTILE);
	Msg.AddInt(1);
	for(unsigned i = 0; i < sizeof(CNetObj_Projectile) / sizeof(int); i++)
		Msg.AddInt(((int *)&p)[i]);

	Server()->SendMsg(&Msg, MSGFLAG_VITAL, ClientID);
	GameWorld()->CreateSound(Character()->m_Pos, SOUND_GUN_FIRE);
}