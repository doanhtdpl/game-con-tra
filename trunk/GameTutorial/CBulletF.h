#ifndef __CBulletF_H__
#define __CBulletF_H__

#include "CGlobal.h"
#include "CBullet.h"
#include "CDynamicObject.h"

class CBullet_F : public CDynamicObject
{
public:
	CBullet_F(void);
	CBullet_F(double rotation, D3DXVECTOR2 pos, D3DXVECTOR2 offset);
	CBullet_F(double rotation, D3DXVECTOR2 pos, D3DXVECTOR2 offset, bool direction);
	~CBullet_F();
	virtual void MoveUpdate(float DeltaTime);
	virtual std::string ClassName(){return __CLASS_NAME__(CBullet_F);};
	virtual void Update(float DeltaTime);
	virtual void Update(float DeltaTime, std::vector<CGameObject*> _listObjectCollision);
	virtual RECT* GetRectRS();
	virtual RECT* GetBound();
	virtual Box GetBox();
public:
	virtual void Init(); // khoi tao vi tri ban dau cua vien dan.
private:
	double m_angle;
	D3DXVECTOR2 m_center;
	double m_rotation;
	D3DXVECTOR2 m_offset;
};

#endif // !__CBulletF_H__
