#ifndef __CMENU_GAME_H__
#define __CMENU_GAME_H__

#include "CStaticObject.h"
#include "CAnimation.h"

class CMenuGame : public CStaticObject, public CAnimation
{
public:
	CMenuGame(void);
	CMenuGame(const std::vector<int>& info);
	~CMenuGame();
	std::string ClassName(){ return __CLASS_NAME__(CMenuGame); };
	virtual void Update(float deltaTime);
	virtual void Move(float deltaTime);
	RECT* GetRectRS();
protected:
	void Init();
	float m_timeDelay;
};

#endif // !__CMENU_GAME_H__
