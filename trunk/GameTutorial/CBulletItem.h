#ifndef __CBulletItem_H__
#define __CBulletItem_H__

#include "CDynamicObject.h"
#include "CAnimation.h"

enum STATE_BULLET_ITEM{
	BULLET_ITEM_M = 0,
	BULLET_ITEM_B = 1,
	BULLET_ITEM_F = 2,
	BULLET_ITEM_S = 3,
	BULLET_ITEM_L = 4,
	BULLET_ITEM_R = 5
};

class CBulletItem : public CDynamicObject, public CAnimation
{
public:
	CBulletItem(void);
	CBulletItem(D3DXVECTOR2 pos);
	CBulletItem(const std::vector<int>& info);
	~CBulletItem();
	std::string ClassName(){ return __CLASS_NAME__(CBulletItem); };
	virtual void MoveUpdate(float deltaTime);
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::vector<CGameObject*>* listObjectCollision);
	void OnCollision(float deltaTime, std::vector<CGameObject*>* listObjectCollision);
	RECT* GetBound();
	RECT* GetRectRS();
	Box GetBox();
	STATE_BULLET_ITEM m_stateItem;
private:
	bool m_isStanding;
protected:
	void Init();
	void SetFrame();
	double m_angle;
};

#endif // !__CBulletItem_H__