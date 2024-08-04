#include "hshotgun.h"
#include <game/generated/server_data.h>
#include <game/server/entities/projectile.h>
#include <stdlib.h>
#include <time.h>

CHShotgun::CHShotgun(CCharacter *pOwnerChar) :
	CWeapon(pOwnerChar)
{
	srand (time (0));
	m_MaxAmmo = g_pData->m_Weapons.m_aId[WEAPON_SHOTGUN].m_Maxammo;
	m_AmmoRegenTime = 700;
	m_FireDelay = g_pData->m_Weapons.m_aId[WEAPON_SHOTGUN].m_Firedelay - 200;
	m_FullAuto = true;
}

bool CHShotgun::BulletCollide(CProjectile *pProj, vec2 Pos, CCharacter *pHit, bool EndOfLife)
{
	if(pHit)
	{
		if(pHit->GetPlayer()->GetCID() == pProj->GetOwner())
			return false;

		pHit->TakeDamage(vec2(942.0f, 0), g_pData->m_Weapons.m_Shotgun.m_pBase->m_Damage, pProj->GetOwner(), WEAPON_SHOTGUN, pProj->GetWeaponID(), false);
	}

	return true;
}

void CHShotgun::Fire(vec2 Direction)
{
	int ShotSpread = 2;
	int ClientID = Character()->GetPlayer()->GetCID();
	int Lifetime = Character()->CurrentTuning()->m_ShotgunLifetime * Server()->TickSpeed();

	vec2 ProjStartPos = Pos() + Direction * GetProximityRadius() * 0.75f;

	CMsgPacker Msg(NETMSGTYPE_SV_EXTRAPROJECTILE);
	Msg.AddInt(ShotSpread * 2 + 1);

	for(int i = -ShotSpread; i <= ShotSpread; ++i)
	{
		float Spreading[] = {-0.15f, -0.1f, 0.0f, 0.1f, 0.15f};
		float a = angle(Direction);
		a += Spreading[i + 2];
		float v = 1 - (absolute(i) / (float)ShotSpread);
		float Speed = mix((float)GameServer()->Tuning()->m_ShotgunSpeeddiff, 1.0f, v);
		CProjectile *pProj = new CProjectile(
			GameWorld(),
			WEAPON_SHOTGUN, //Type
			GetWeaponID(), //WeaponID
			ClientID, //Owner
			ProjStartPos, //Pos
			vec2(cosf(a), sinf(a)) * Speed, //Dir
			12.0f, // Radius
			Lifetime * 2, //Span
			BulletCollide);

		// pack the Projectile and send it to the client Directly
		CNetObj_Projectile p;
		pProj->FillInfo(&p);

		for(unsigned i = 0; i < sizeof(CNetObj_Projectile) / sizeof(int); i++)
			Msg.AddInt(((int *)&p)[i]);
	}

	Server()->SendMsg(&Msg, MSGFLAG_VITAL, ClientID);
	GameWorld()->CreateSound(Pos(), SOUND_SHOTGUN_FIRE);
}