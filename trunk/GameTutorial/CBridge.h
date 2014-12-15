#ifndef __CBRIDGE_H__
#define __CBRIDGE_H__

#include "CStaticObject.h"
#include "CAnimation.h"
#include "CExplosionEffect.h"

enum STATE_BRIDGE{
	X4 = 0,
	X3 = 1,
	X2 = 2,
	X = 3,
	NONE = 4
};

class CBridge : public CStaticObject, public CAnimation
{
public:
	CBridge(void);
	CBridge(const std::vector<int>& info);
	~CBridge();
	std::string ClassName(){ return __CLASS_NAME__(CBridge); };
	virtual void SetFrame(float deltaTime);
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::hash_map<int, CGameObject*>* listObjectCollision);
	void OnCollision(float deltaTime, std::vector<CGameObject*>* listObjectCollision);
	RECT* GetBound();
	RECT* GetRectRS();
	Box GetBox();
protected:
	void Init();
	float m_timeDelay;
	STATE_BRIDGE m_stateCurrent;
public:
	CExplosionEffect* effect;
};

#endif // !__CBRIDGE_H__
