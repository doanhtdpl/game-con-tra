#ifndef __CSTATEMENU_H__
#define __CSTATEMENU_H__
#include "CState.h"

class CStateMenu : public CState
{
public:
	CStateMenu();
	virtual ~CStateMenu();
	void Init();
	void Update();
	void Render();
	void Destroy();
protected:
};

#endif // !__CSTATEMENU_H__

