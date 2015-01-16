#ifndef __CWORD_H__
#define __CWORD_H__

#include "CStaticObject.h"
#include "CAnimation.h"

class CWord : public CStaticObject, public CAnimation
{
public:
	CWord(int number);
	CWord(const std::vector<int>& info);
	~CWord();
	std::string ClassName(){ return __CLASS_NAME__(CWord); };
	virtual void Update(float deltaTime);
	RECT* GetRectRS();
protected:
	void Init();
	void InitWord();
	float m_timeDelay;
	int m_numberWord;
};

#endif // !__CWORD_H__
