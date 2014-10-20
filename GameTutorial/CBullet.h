#ifndef __CBULLET_H__
#define __CBULLET_H__

#include "CDynamicObject.h"

enum SHOOT
{
	IS_NORMAL = 0,
	IS_UP = 1,
	IS_DOWN = 2,
	IS_DIAGONAL_UP = 3,
	IS_DIAGONAL_DOWN = 4
};

class CBullet : public CDynamicObject
{
public:
	CBullet(void);
	~CBullet(void);
public:
	virtual void MoveUpdate(float DeltaTime);// overide IMOVE
	virtual std::string ClassName(){return __CLASS_NAME__(CBullet);};
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::vector<CGameObject*> _listObjectCollision);
	virtual RECT* GetRectRS();
	virtual RECT GetRect();
protected:
	void InitPosotion(); //Khoi tao vi tri ban dau cua vien dan
	int m_shootState; //Trang thai dan hien tai
	D3DXVECTOR2 m_posStart; //Vi tri ban dau cua vien dan
	D3DXVECTOR2 m_offset; //Vi tri cua vien dan so voi contra
	float m_rotation(); //Goc ban
};

#endif // !__CBULLET_H__
