#include "CFactoryStaticObject.h"
#include "CHidenObject.h"
#include "CSWeapon.h"
#include "CWallTurret.h"
#include "CGroundCannon.h"
#include "CSniper.h"
#include "CBridge.h"
#include "CDefenseCannon.h"
#include "CSoldier.h"

CFactoryStaticObject::~CFactoryStaticObject()
{

}

CGameObject* CFactoryStaticObject::CreateObject(int idObject)
{
	switch(idObject)
	{
	case 1001:
		{
			return nullptr;
		}
	}
}

CGameObject* CFactoryStaticObject::CreateObject(const std::vector<int>& info)
{
	int idType;
	if(!info.empty())
	{
		idType = info.at(0);
		switch(idType)
		{
		case 15001:
		case 15002:
		case 15003:	// sjnh weapon
		case 15004:	// sinh enemy
		case 15006:
		case 15007:
		case 14002: //Dan F
		case 14003: //Dan L
		case 14004: //Dan M
		case 14005: //Dan R
		case 14006: //Dan S
		case 14001: //Dan S
			{
				return new CHidenObject(info);
			}
			// TT
		case 11000:
			{
				return new CSoldier(info);
			}
		case 11001: case 11002:
			{
				return new CSniper(info);
			}
		case 11003: //Wallturret
			{
				return new CWallTurret(info);
			}
		case 11004: //Cannon
			{
				return new CGroundCanon(info);
			}
			//case 13001: //Weapon tinh
			//	{
			//		return new CSWeapon(info);
			//	}
		case 13002: //Dan F
		case 13003: //Dan L
		case 13004: //Dan M
		case 13005: //Dan R
		case 13006: //Dan S
		case 13001: //Dan S
			{
				return new CSWeapon(info);
			}
		case 16001:
			{
				return new CBridge(info);
			}

		case 17001://Boss map 1
			{
				return new CDefenseCannon(info);
			}
		default:
			return nullptr;
		}
	}
	return nullptr;
}