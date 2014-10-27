#include "CFactoryStaticObject.h"
#include "CHidenObject.h"

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
		}
	}
	return nullptr;
}