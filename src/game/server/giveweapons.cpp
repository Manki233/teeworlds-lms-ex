//#include <game/server/player.h>
//#include <game/server/weapons.h>
//
//#include <game/server/entities/character.h>
//
//#include "giveweapons.h"
//
//void GiveWeapons (CPlayer *pPlayer) {
//	CCharacter *pChr = pPlayer->GetCharater();
//	
//	for (int i = 1 ; i <= 5 ; i ++)
//	{
//		int weapon_id = pChr->GetPlayer()->m_PickWeapons[i];
//
//		switch (weapon_id) {
//			case WEAPON_ID_HAMMER:
//				pChr->GiveWeapon(WEAPON_HAMMER, WEAPON_ID_HAMMER, -1);
//				break;
//			case WEAPON_ID_PISTOL:
//				pChr->GiveWeapon(WEAPON_GUN, WEAPON_ID_PISTOL, 5);
//				break;
//			case WEAPON_ID_SHOTGUN:
//				pChr->GiveWeapon(WEAPON_SHOTGUN, WEAPON_ID_SHOTGUN, 10);
//				break;
//			case WEAPON_ID_GRENADE:
//				pChr->GiveWeapon(WEAPON_GRENADE, WEAPON_ID_GRENADE, 10);
//				break;
//			case WEAPON_ID_LASER:
//				pChr->GiveWeapon(WEAPON_LASER, WEAPON_ID_LASER, 10);
//				break;
//			case WEAPON_ID_EXPLODINGLASER:
//				pChr->GiveWeapon(WEAPON_LASER, WEAPON_ID_EXPLODINGLASER, 10);
//				break;
//			case WEAPON_ID_HSHOTGUN:
//				pChr->GiveWeapon(WEAPON_SHOTGUN, WEAPON_ID_HSHOTGUN, 10);
//				break;
//			case WEAPON_ID_EHAMMER:
//				pChr->GiveWeapon(WEAPON_HAMMER, WEAPON_ID_EHAMMER, -1);
//				break;
//			case WEAPON_ID_PHAMMER:
//				pChr->GiveWeapon(WEAPON_HAMMER, WEAPON_ID_PHAMMER, -1);
//				break;
//			case WEAPON_ID_PPISTOL:
//				pChr->GiveWeapon(WEAPON_GUN, WEAPON_ID_PPISTOL, 3);
//				break;
////			case WEAPON_ID_NINJA:
////				pChr->GiveWeapon(WEAPON_NINJA, WEAPON_ID_NINJA, -1);
////				break;
//		}
//	}
//}
