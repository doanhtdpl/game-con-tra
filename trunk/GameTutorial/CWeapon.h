#ifndef __CWEAPON_H__
#define __CWEAPON_H__

#include "CDynamicObject.h"
#include "CExplosionEffect.h"
#include "CBulletItem.h"

class CWeapon : public CDynamicObject
{
public:
	CWeapon(void);
	CWeapon(const std::vector<int>& info);
	~CWeapon();
	std::string ClassName(){return __CLASS_NAME__(CWeapon);};
	virtual void MoveUpdate(float deltaTime);
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::vector<CGameObject*>* listObjectCollision);
	void OnCollision(float deltaTime, std::vector<CGameObject*>* listObjectCollision);
	RECT* GetBound();
	RECT* GetRectRS();
	Box GetBox();
protected:
	void Init();
	double m_angle;
public:
	STATE_BULLET_ITEM m_stateItem;
};

#endif // !__CWEAPON_H__
