#ifndef __CSTATELOGO_H__
#define __CSTATELOGO_H__
#include "CState.h"
#include <iostream>
class CStateLogo : public CState
{
public:
	CStateLogo();
	virtual ~CStateLogo();
	void Init();
	void Update();
	void Render();
	void Destroy();
protected:
	int m_count;
};

#endif // !__CSTATELOGO_H__

