#ifndef __CBulletDefenseCannon_H__
#define __CBulletDefenseCannon_H__

#include "CBullet.h"

class CBullet_DefenseCannon : public CBullet
{
public:
	CBullet_DefenseCannon(void);
	CBullet_DefenseCannon(double rotation, D3DXVECTOR2 pos, D3DXVECTOR2 offset);
	CBullet_DefenseCannon(double rotation, D3DXVECTOR2 pos, D3DXVECTOR2 offset, bool direction);
	~CBullet_DefenseCannon(void);
public:
	virtual void MoveUpdate(float DeltaTime);
	virtual std::string ClassName(){ return __CLASS_NAME__(CBullet_DefenseCannon); };
	virtual void Update(float DeltaTime);
	virtual void Update(float DeltaTime, std::vector<CGameObject*>* _listObjectCollision);
	virtual void OnCollision(float deltaTime, std::vector<CGameObject*>* listObjectCollision);

	virtual RECT* GetRectRS();
	virtual RECT* GetBound();
	virtual Box GetBox();
protected:
	virtual void Init(); // khoi tao vi tri ban dau cua vien dan.
	D3DXVECTOR2 m_offset;//Vi tri cua vien dan so voi Sung
	double m_rotation;//Goc ban dan
	double m_time;
};

#endif // !__CBulletDefenseCannon_H__
