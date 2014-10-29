#ifndef __CSTATELOGO_H__
#define __CSTATELOGO_H__
#include "CState.h"
#include <iostream>
#include "CSprite.h"
#include "CTexture.h"
#include "CContra.h"
#include "CDynamicObject.h"
#include "CHidenObject.h"
#include "CSoldier.h"
#include "CSniper.h"
#include "CWallTurret.h"

class CStateLogo : public CState
{
public:
	CStateLogo();
	virtual ~CStateLogo();
	void Init();
	void Update(float deltaTime);
	void Render();
	void Destroy();
protected:
	CHidenObject* hideObj;
	CSoldier* sObj;
	CSniper* nobj;
	CWallTurret* wobj;
	// Test collision
	Box first;
	Box second;
	Box broadphaseBox;
	bool isCollision;
	float collisiontime;
	float increse;
};

#endif // !__CSTATELOGO_H__

