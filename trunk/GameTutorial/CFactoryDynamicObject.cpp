#include "CFactoryDynamicObject.h"
#include "CWeapon.h"
#include "CSniper.h"
#include "CSoldier.h"

CFactoryDynamicObject::~CFactoryDynamicObject()
{

}

CGameObject* CFactoryDynamicObject::CreateObject(int idObject)
{
	switch(idObject)
	{
	case 1001:
		{
			return nullptr;
		}
	}
}

CGameObject* CFactoryDynamicObject::CreateObject(const std::vector<int>& info)
{
	int idObject;
	float posX;
	float posY;
	if(!info.empty())
	{
		idObject = info.at(0);
		posX = info.at(1);
		posY = info.at(2);
		switch(idObject)
		{
		case 20002:
			{
				return new CWeapon(info);
			}
		case 11000:
			{
				return new CSoldier(info);
			}
		case 11001:
			{
				return new CSniper(info);
			}
		}
	}
	return nullptr;
}