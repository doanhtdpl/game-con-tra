#include "CFactoryStaticObject.h"
#include "CHidenObject.h"
#include "CSWeapon.h"
#include "CWallTurret.h"

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
		case 13001:
			{
				return new CHidenObject(info);
				break;
			}
		case 20003:
			{
				return new CSWeapon(info);
			}
		case 11002:
			{
				return new CWallTurret(info);
			}
		}
	}
	return nullptr;
}