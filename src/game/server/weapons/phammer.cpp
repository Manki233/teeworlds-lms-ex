#include "phammer.h"

#include <game/generated/server_data.h>
#include <game/server/entities/projectile.h>
#include <game/server/entities/wall.h>
#include <game/server/entities/circle.h>

CPHammer::CPHammer(CCharacter *pOwnerChar) :
	CWeapon(pOwnerChar)
{
	m_MaxAmmo = g_pData->m_Weapons.m_aId[WEAPON_HAMMER].m_Maxammo;
	m_AmmoRegenTime = g_pData->m_Weapons.m_aId[WEAPON_HAMMER].m_Ammoregentime;
	m_FireDelay = g_pData->m_Weapons.m_aId[WEAPON_HAMMER].m_Firedelay;

	m_OwnerID = pOwnerChar->GetPlayer()->GetCID();

	mTmp = 0;
}

void CPHammer::Fire(vec2 Direction)
{
	int ClientID = Character()->GetPlayer()->GetCID();
	GameWorld()->CreateSound(Pos(), SOUND_HAMMER_FIRE);

	GameServer()->Antibot()->OnHammerFire(ClientID);

	if(Character()->IsSolo() || Character()->m_Hit & CCharacter::DISABLE_HIT_HAMMER)
		return;

	vec2 HammerHitPos = Pos() + Direction * GetProximityRadius() * 0.75f;

	CCharacter *apEnts[MAX_CLIENTS];
	int Hits = 0;
	int Num = GameWorld()->FindEntities(HammerHitPos, GetProximityRadius() * 10.0f, (CEntity **)apEnts,
		MAX_CLIENTS, CGameWorld::ENTTYPE_CHARACTER);

	for (auto i = 0 ; i < Num ; i ++)
		new CWall (GameWorld(), HammerHitPos, 
			apEnts[i]->GetPos(), 1, ClientID, 2);

	float FireDelay;
	int TuneZone = Character()->m_TuneZone;
	FireDelay = g_pData->m_Weapons.m_aId[WEAPON_HAMMER].m_Firedelay;
	m_ReloadTimer = FireDelay * Server()->TickSpeed() / 1000;
}

void CPHammer::OnTick() {
	Character()->m_DamageScale = 0.5f;

	mTmp ++;

	if (mTmp >= 20 && GameServer()->GetPlayerChar(m_OwnerID))
	{
		mTmp = 0;
		new CCircle(GameWorld(), GameServer()->GetPlayerChar(m_OwnerID)->GetPos(), vec2(0.0f, 0.0f),
			0, 0, 20, 64, 1, 8, 0, &GameServer()->GetPlayerChar(m_OwnerID)->m_Core.m_Pos);

		GameServer()->SendBroadcast("你正处于 50% 减伤下！", m_OwnerID);
	}
}