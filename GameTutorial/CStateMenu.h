#ifndef __CSTATEMENU_H__
#define __CSTATEMENU_H__
#include "CState.h"
#include "CMenuGame.h"
#include "CScoreScense.h"

class CStateMenu : public CState
{
public:
	CStateMenu();
	virtual ~CStateMenu();
	void Init();
	void Update(float deltaTime);
	void Render();
	void Destroy();
protected:
	CMenuGame* mainMenu;
	CScoreScense* scoreScense;
};

#endif // !__CSTATEMENU_H__

