#ifndef __CBulletItem_H__
#define __CBulletItem_H__

#include "CDynamicObject.h"
#include "CAnimation.h"

enum STATE_BULLET_ITEM{
	BULLET_ITEM_B = 130001,
	BULLET_ITEM_F = 130002,
	BULLET_ITEM_L = 130003,
	BULLET_ITEM_M = 130004,
	BULLET_ITEM_R = 130005,
	BULLET_ITEM_S = 130006
};

class CBulletItem : public CDynamicObject, public CAnimation
{
public:
	CBulletItem(void);
	CBulletItem(D3DXVECTOR2 pos);
	CBulletItem(D3DXVECTOR2 pos, STATE_BULLET_ITEM state);
	CBulletItem(const std::vector<int>& info);
	~CBulletItem();
	std::string ClassName(){ return __CLASS_NAME__(CBulletItem); };
	virtual void MoveUpdate(float deltaTime);
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::vector<CGameObject*>* listObjectCollision);
	void OnCollision(float deltaTime, std::vector<CGameObject*>* listObjectCollision);
	void Init();
	RECT* GetBound();
	RECT* GetRectRS();
	Box GetBox();
	STATE_BULLET_ITEM m_stateItem;
protected:
	void SetFrame();
};

#endif // !__CBulletItem_H__