#include "CFactoryStaticObject.h"
#include "CSimon.h"

CFactoryStaticObject::~CFactoryStaticObject()
{

}

CGameObject* CFactoryStaticObject::CreateObject(int idObject)
{
	switch(idObject)
	{
	case 1001:
		return new CSimon();
	}
}