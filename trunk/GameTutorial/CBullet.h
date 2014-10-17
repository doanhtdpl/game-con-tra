#ifndef __CBULLET_H__
#define __CBULLET_H__

#include "CDynamicObject.h"

class CBullet : public CDynamicObject
{
public:
	CBullet(void);
	~CBullet(void);
protected:
	virtual void MoveUpdate(float DeltaTime);// overide IMOVE
	virtual std::string ClassName(){return __CLASS_NAME__(CBullet);};
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::vector<CGameObject*> _listObjectCollision);
};

#endif // !__CBULLET_H__
