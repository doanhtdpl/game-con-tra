#ifndef __CBULLET_S_H__
#define __CBULLET_S_H__

#include "CGlobal.h"
#include "CBullet.h"

class CBullet_S : public CBullet
{
public:
	CBullet_S();
	~CBullet_S();
	CBullet_S(double rotation);
	virtual void MoveUpdate(float DeltaTime);// overide IMOVE
	virtual std::string ClassName(){return __CLASS_NAME__(CBullet);};
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::vector<CGameObject*> _listObjectCollision);
	virtual RECT* GetRectRS();
	virtual RECT GetRect();
public:
	virtual void InitPosition(); //Khoi tao vi tri ban dau cua vien dan
	CBullet* m_bullet_1;
	CBullet* m_bullet_2;
	CBullet* m_bullet_3;
	CBullet* m_bullet_4;
	CBullet* m_bullet_5;
};

#endif // !__CBULLET_S_H__
