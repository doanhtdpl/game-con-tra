#ifndef __CBulletF_H__
#define __CBulletF_H__

#include "CGlobal.h"
#include "CBullet.h"

class CBullet_F: public CBullet
{
public:
	CBullet_F();
	~CBullet_F();
	CBullet_F(double rotation);
	virtual void MoveUpdate(float DeltaTime);
	virtual std::string ClassName(){return __CLASS_NAME__(CBullet_F);};
	virtual void Update(float DeltaTime);
	virtual void Update(float DeltaTime, std::vector<CGameObject*> _listObjectCollision);
	virtual RECT* GetRectRS();
	virtual RECT GetRect();
public:
	virtual void InitPosition(); // khoi tao vi tri ban dau cua vien dan.
private:
	double m_angle;
	D3DXVECTOR2 m_posStart;
	D3DXVECTOR2 m_center;
};

#endif // !__CBulletF_H__
