#ifndef __CSIMON_H__
#define __CSIMON_H__
#include "CDynamicObject.h"
#include "CAnimation.h"

class CSimon : public CDynamicObject, CAnimation
{
public:
	CSimon();
	~CSimon();
	std::string ClassName(){ return __CLASS_NAME__(CSimon);};
	virtual void MoveUpdate(float deltaTime);
	void ChangeFrame(float deltaTime);
	virtual void Update(float deltaTime);
	virtual void Update(float deltaTime, std::vector<CGameObject*> listObjectCollision);
	RECT GetRect();
	RECT* GetRectRS();
protected:
	int m_endFrame;
	int m_startFrame;
};

#endif // !__CSimon_H__
