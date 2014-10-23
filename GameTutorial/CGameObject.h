#ifndef __CGAMEOBJECT__H__
#define __CGAMEOBJECT__H__

#include "CGlobal.h"

class CGameObject
{
protected:
	int m_id;//each object has a ID to identified with other object
	int m_idType; // Thuoc loai doi tuong nao
	int m_idImage;
	D3DXVECTOR2 m_pos;//position of object
	float m_posZ;//xet thang nao ve tren. mac dinh  = 0
	bool m_isALive;//life or die??
	int m_height;//height of object and uses to draw.
	int m_width;

	bool m_isAnimatedSprite;//default = false, but when object iherit IAnimatedSprite-> True;
	bool m_left;//Direction. Default left
	RECT *m_rectRS;//NULL if object hasn't animated sprite

	RECT m_rect;//xen trong Quadtree

public:
	virtual std::string ClassName() = 0;
	CGameObject(void);
	CGameObject(std::vector<std::string> arr);
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::vector<CGameObject*> listObjectCollision);
	virtual D3DXVECTOR2 GetPos(){return this->m_pos;};
	int GetID(){return this->m_id;};
	int GetIDType(){return this->m_idType;};
	bool GetDirection(){return this->m_left;};
	float GetWidth(){return this->m_width;};
	float GetHeight(){return this->m_height;};
	bool IsAlive(){return this->m_isALive;};
	RECT* GetBox();
	virtual RECT GetRect();
	virtual RECT* GetRectRS();
	~CGameObject(void);
};

#endif // !__OBJECT_GAME__H__