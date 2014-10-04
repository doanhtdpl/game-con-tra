#ifndef __CCONTRA_H__
#define __CCONTRA_H__
#include "CDynamicObject.h"
#include "CAnimation.h"

class CContra : public CDynamicObject, CAnimation
{
public:
	CContra();
	~CContra();
	std::string ClassName(){ return __CLASS_NAME__(CContra);};
	virtual void MoveUpdate(float deltaTime);
	void ChangeFrame(float deltaTime);
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::vector<CGameObject*> listObjectCollision);
	RECT GetRect();
	RECT* GetRectRS();
protected:

};

#endif // !__CCONTRA_H__
