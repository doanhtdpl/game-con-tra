#ifndef __CBULLET_N_H__
#define __CBULLET_N_H__

#include "CBullet.h"

class CBullet_N : public CBullet
{
public:
	CBullet_N(void);
	CBullet_N(double rotation, D3DXVECTOR2 pos, D3DXVECTOR2 offset);
	CBullet_N(double rotation, D3DXVECTOR2 pos, D3DXVECTOR2 offset, bool direction);
	~CBullet_N(void);
public:
	virtual void MoveUpdate(float DeltaTime);// overide IMOVE
	virtual std::string ClassName(){return __CLASS_NAME__(CBullet_N);};
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::vector<CGameObject*> _listObjectCollision);
	virtual RECT* GetRectRS();
	virtual RECT* GetBound();
	virtual Box GetBox();
protected:
	virtual void Init(); //Khoi tao vi tri ban dau cua vien dan
	D3DXVECTOR2 m_offset; //Vi tri cua vien dan so voi contra
	double m_rotation; //Goc ban
};

#endif // !__CBULLET_H__
