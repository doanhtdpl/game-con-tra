#ifndef __STATIC_OBJECT__H__
#define __STATIC_OBJECT__H__

#include "CGameObject.h"

class StaticObject : public CGameObject
{
public:
	virtual std::string className() = 0;
	StaticObject(void);
	StaticObject(std::vector<std::string> arr);
	~StaticObject(void);
	virtual void update(float deltaTime);
	virtual void update(float deltaTime, std::vector<CGameObject*> listObjectCollision);
};
// ;)
#endif