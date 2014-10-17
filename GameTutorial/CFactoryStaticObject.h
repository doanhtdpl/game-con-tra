#ifndef __CFACTORY_STATIC_OBJECT_H__
#define ____CFACTORY_STATIC_OBJECT_H__

#include "CGlobal.h"
#include "CFactoryObject.h"
#include "CGameObject.h"

class CFactoryStaticObject : public CFactoryObject
{
public:
	CFactoryStaticObject() : CFactoryObject(){};
protected:
	~CFactoryStaticObject();
	virtual CGameObject* CreateObject(int idObject);
};

#endif // !__CFACTORY_STATIC_OBJECT_H__
