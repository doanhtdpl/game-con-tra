#ifndef __CWEAPON_H__
#define __CWEAPON_H__

#include "CDynamicObject.h"

class CWeapon : public CDynamicObject
{
public:
	CWeapon(void);
	CWeapon(const std::vector<int>& info);
	~CWeapon();
	std::string ClassName(){return __CLASS_NAME__(CWeapon);};
	virtual void MoveUpdate(float deltaTime);
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::hash_map<int, CGameObject*>* listObjectCollision);
	RECT* GetBound();
	RECT* GetRectRS();
	Box GetBox();
protected:
	void Init();
	double m_angle;

};

#endif // !__CWEAPON_H__
