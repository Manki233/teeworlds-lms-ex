#include "grenade.h"
#include <game/generated/server_data.h>
#include <game/server/entities/projectile.h>

CGrenade::CGrenade(CCharacter *pOwnerChar) :
	CWeapon(pOwnerChar)
{
	m_MaxAmmo = g_pData->m_Weapons.m_aId[WEAPON_GRENADE].m_Maxammo;
	m_AmmoRegenTime = 1400;
	m_FireDelay = g_pData->m_Weapons.m_aId[WEAPON_GRENADE].m_Firedelay;
	m_FullAuto = true;
}

bool CGrenade::GrenadeCollide(CProjectile *pProj, vec2 Pos, CCharacter *pHit, bool EndOfLife)
{
	if(pHit && pHit->GetPlayer()->GetCID() == pProj->GetOwner()) {
		return false;
	}

	CCharacter *apEnts[MAX_CLIENTS];

	float Radius = 135.0f;

	int Num = pProj->GameWorld()->FindEntities(Pos, Radius, (CEntity **)apEnts, MAX_CLIENTS, CGameWorld::ENTTYPE_CHARACTER);

	int own = -1;
	
	for(int i = 0; i < Num; i++)
	{
		if (apEnts[i]->GetPlayer()->GetCID() == pProj->GetOwner())
		{
			apEnts[i]->IncreaseHealth(3);
			apEnts[i]->IncreaseArmor(3);
			own = i;
		}
	}

	if (own != -1)
	{
		apEnts[own]->IncreaseArmor(3);
	}

	pProj->GameWorld()->CreateExplosion(Pos, pProj->GetOwner(), WEAPON_GRENADE, pProj->GetWeaponID(), g_pData->m_Weapons.m_aId[WEAPON_GRENADE].m_Damage / 2, pProj->GetOwner() < 0);
	pProj->GameWorld()->CreateSound(Pos, SOUND_GRENADE_EXPLODE);

	return true;
}

void CGrenade::Fire(vec2 Direction)
{
	int ClientID = Character()->GetPlayer()->GetCID();
	int Lifetime = Character()->CurrentTuning()->m_GrenadeLifetime * Server()->TickSpeed();

	vec2 ProjStartPos = Pos() + Direction * GetProximityRadius() * 0.75f;

	CProjectile *pProj = new CProjectile(
		GameWorld(),
		WEAPON_GRENADE, //Type
		GetWeaponID(), //WeaponID
		ClientID, //Owner
		ProjStartPos, //Pos
		Direction, //Dir
		6.0f, // Radius
		Lifetime, //Span
		GrenadeCollide);

	// pack the Projectile and send it to the client Directly
	CNetObj_Projectile p;
	pProj->FillInfo(&p);

	CMsgPacker Msg(NETMSGTYPE_SV_EXTRAPROJECTILE);
	Msg.AddInt(1);
	for(unsigned i = 0; i < sizeof(CNetObj_Projectile) / sizeof(int); i++)
		Msg.AddInt(((int *)&p)[i]);

	Server()->SendMsg(&Msg, MSGFLAG_VITAL, ClientID);
	GameWorld()->CreateSound(Character()->m_Pos, SOUND_GRENADE_FIRE);
}