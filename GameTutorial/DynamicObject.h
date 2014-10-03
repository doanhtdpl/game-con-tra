#ifndef __DYNAMIC_OBJECT_H__
#define __DYNAMIC_OBJECT_H__


#include "CGameObject.h"
#include "CMove.h"
#include <list>

class DynamicObject : public CGameObject, public CMove
{
public:
	virtual void move(float Delta_Time);// overide IMOVE
	virtual std::string className();
	virtual void update(float deltatime);
	virtual void update(float delta_Time, std::vector<CGameObject*> _listObjectCollision);

	DynamicObject(void);
	DynamicObject(std::vector<std::string> arr);
	~DynamicObject(void);
};

#endif // !__DYNAMIC_OBJECT_H__