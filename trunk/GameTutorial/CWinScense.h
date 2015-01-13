#ifndef __CWIN_SCENSE_H__
#define __CWIN_SCENSE_H__

#include "CStaticObject.h"
#include "CAnimation.h"

class CWinScense : public CStaticObject, public CAnimation
{
public:
	CWinScense(void);
	CWinScense(const std::vector<int>& info);
	~CWinScense();
	std::string ClassName(){ return __CLASS_NAME__(CWinScense); };
	virtual void Update(float deltaTime);
	virtual void Move(float deltaTime);
	RECT* GetRectRS();
protected:
	void Init();
	float m_timeDelay;
};

#endif // !__CWIN_SCENSE_H__
