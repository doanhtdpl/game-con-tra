#include "CFactoryStaticObject.h"
#include "CHidenObject.h"
#include "CSWeapon.h"
#include "CWallTurret.h"
#include "CGroundCannon.h"

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
			{
				return new CHidenObject(info);
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
		case 13001: //Dan F
		case 13002: //Dan L
		case 13003: //Dan M
		case 13004: //Dan R
		case 13005: //Dan S
			{
				return new CSWeapon(info);
			}
		default:
			return nullptr;
		}
	}
	return nullptr;
}