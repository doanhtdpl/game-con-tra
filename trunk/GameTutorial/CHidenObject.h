#ifndef __CHIDEN_OBJECT_H__
#define __CHIDEN_PBJECT_H__
#include "CStaticObject.h"
#include "CGlobal.h"

enum HIDEN_OBJECT_TYPE
{
	ON_GROUND = 15001,
	UNDER_WATER = 15002
};

class CHidenObject : public CStaticObject
{
public:
	CHidenObject(void);
	CHidenObject(HIDEN_OBJECT_TYPE type);
	CHidenObject(const std::vector<int>& info);
	~CHidenObject();
	virtual std::string ClassName(){return __CLASS_NAME__(CHidenObject);}
	virtual HIDEN_OBJECT_TYPE GetHidenObjectType(){return m_type;}
	virtual void SetHidenObjectType(HIDEN_OBJECT_TYPE type){this->m_type = type;};
	virtual Box GetBox();
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::vector<CGameObject*> listObjectCollision);
	//sang test va cham
	virtual RECT* GetRectRS();
protected:
	HIDEN_OBJECT_TYPE m_type;
};

#endif // !__CHIDEN_OBJECT_H__