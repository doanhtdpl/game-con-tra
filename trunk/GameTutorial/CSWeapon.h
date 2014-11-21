#ifndef __CSWEAPON_H__
#define __CSWEAPON_H__

#include "CStaticObject.h"
#include "CAnimation.h"

class CSWeapon : public CStaticObject, public CAnimation
{
public:
	CSWeapon(void);
	CSWeapon(const std::vector<int>& info);
	~CSWeapon();
	std::string ClassName(){return __CLASS_NAME__(CSWeapon);};
	virtual void SetFrame(float deltaTime);
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::hash_map<int, CGameObject*>* listObjectCollision);
	RECT* GetBound();
	RECT* GetRectRS();
	Box GetBox();
protected:
	void Init();
	float m_timeDelay;

};

#endif // !__CSWEAPON_H__