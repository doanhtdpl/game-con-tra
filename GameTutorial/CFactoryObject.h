#ifndef __CFACTORY_OBJECT_H__
#define __CFACTORY_OBJECT_H__

#include "CGlobal.h"
#include "CSingleton.h"
#include "CGameObject.h"

class CFactoryObject : public CSingleton<CFactoryObject>
{
	friend class CSingleton<CFactoryObject>;
public:
	~CFactoryObject(){};
protected:
	CFactoryObject(){};
	virtual CGameObject* CreateObject(int idObject) = 0;
};

#endif // !__CFACTORY_OBJECT_H__
