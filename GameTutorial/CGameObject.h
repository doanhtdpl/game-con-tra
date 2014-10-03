#ifndef __CGAMEOBJECT__H__
#define __CGAMEOBJECT__H__

#include <d3dx9.h>
#include <list>
#include <vector>
#include <string>

class CGameObject
{
public:
	int _ID;//each object has a ID to identified with other object
	int _ID_Image;
	D3DXVECTOR2 _pos;//position of object
	float z;//xet thang nao ve tren. mac dinh  = 0
	bool _isALive;//life or die??
	int _height;//height of object and uses to draw.
	int _width;

	bool _isAnimatedSprite;//default = false, but when object iherit IAnimatedSprite-> True;
	bool _Left;//Direction. Default left
	RECT *_rectRS;//NULL if object hasn't animated sprite

	RECT _rect;//xen trong Quadtree

public:
	virtual std::string className() = 0;
	CGameObject(void);
	CGameObject(std::vector<std::string> arr);
	virtual void update(float deltaTime);
	virtual void update(float deltaTime, std::vector<CGameObject*> listObjectCollision);
	virtual RECT getRect();
	~CGameObject(void);
};

#endif // !__OBJECT_GAME__H__