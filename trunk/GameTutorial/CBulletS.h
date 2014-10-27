#ifndef __CBULLET_S_H__
#define __CBULLET_S_H__

#include "CGlobal.h"
#include "CBullet.h"
#include "CAnimation.h"

class CBullet_S : public CBullet, public CAnimation
{
public:
	CBullet_S();
	~CBullet_S();
	CBullet_S(double rotation, D3DXVECTOR2 pos, D3DXVECTOR2 offset);
	CBullet_S(double rotation, D3DXVECTOR2 pos, D3DXVECTOR2 offset, bool direction);
	virtual void MoveUpdate(float DeltaTime);// overide IMOVE
	virtual std::string ClassName(){return __CLASS_NAME__(CBullet_S);};
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::vector<CGameObject*> _listObjectCollision);
	virtual void ChangeFrame(float deltaTime);
	virtual RECT* GetRectRS();
	virtual RECT* GetBound();
public:
	virtual void Init(); //Khoi tao vi tri ban dau cua vien dan
	CBullet_S* m_bullet_1;
	CBullet_S* m_bullet_2;
	CBullet_S* m_bullet_3;
	CBullet_S* m_bullet_4;
	CBullet_S* m_bullet_5;
};

#endif // !__CBULLET_S_H__
